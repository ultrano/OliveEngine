#include "OvResourceManager.h"
#include "OvFileMeshLoader.h"
#include "OvMesh.h"
#include "OvTextureLoader.h"
#include "OvTexture.h"
#include "OvShaderCodeLoader.h"
#include "OvShaderCode.h"
#include "OvMaterialLoader.h"
#include "OvMaterial.h"

#include <algorithm>
#include <process.h>


OvResourceManager::OvResourceManager()
{
	::InitializeCriticalSection( &m_load_section );
	::InitializeCriticalSection( &m_life_section );

	m_loaderTable[ OvMesh			::GetRTTI() ]	= OvNew OvFileMeshLoader;
	m_loaderTable[ OvTexture		::GetRTTI() ]	= OvNew OvTextureLoader;
	m_loaderTable[ OvShaderCode		::GetRTTI() ]	= OvNew OvShaderCodeLoader;
	m_loaderTable[ OvMaterial		::GetRTTI() ]	= OvNew OvMaterialLoader;

	m_resourceDirectory.resize( 1024 );
	GetModuleFileName( NULL, (LPCH)m_resourceDirectory.c_str(), (DWORD)m_resourceDirectory.size() );

	m_resourceDirectory = OvGetDirectoryInFullFilePath( m_resourceDirectory );
	m_resourceDirectory = OvGetDirectoryInFullFilePath( m_resourceDirectory );
	m_resourceDirectory = OvGetDirectoryInFullFilePath( m_resourceDirectory );
	m_resourceDirectory += "\\resource";

	m_resourceDirectory.resize( m_resourceDirectory.length() );

	m_async_handle = (HANDLE)_beginthread( OvResourceManager::_thread_routine, 0, (void*)this );

}

OvResourceManager::~OvResourceManager()
{

	_get_async_life_flag() = false;
	WaitForSingleObject( m_async_handle, INFINITE );

	m_cacheList.clear();
	::DeleteCriticalSection( &m_load_section );
	::DeleteCriticalSection( &m_life_section );

}

OvResourceSPtr OvResourceManager::LoadResource( const OvRTTI* resourceType, const OvString& fileLocation )
{
	OvResourceSPtr resource = NULL;
	resource = _find_loaded_resource( resourceType, fileLocation );
	if ( NULL == resource )
	{
		if ( OvResourceLoaderSPtr loader = _find_resource_loader( resourceType ) )
		{
			if ( resource = loader->_load_resource( fileLocation ) )
			{
				_register_loaded_resource( fileLocation, resource.GetRear() );
				return resource;
			}
		}
	}
	return resource;
}

OvResourceSPtr OvResourceManager::LoadResource( const OvString& resourceType, const OvString& fileLocation )
{
	for each( const resource_loader_table::value_type& typevalue in m_loaderTable )
	{
		OvRTTI* rtti = const_cast<OvRTTI*>( typevalue.first );
		if ( rtti->TypeName() == resourceType )
		{
			return LoadResource( rtti, fileLocation );
		}
	}
	return NULL;
}
OvResourceTicketSPtr OvResourceManager::AsyncLoadResource( const OvRTTI* resourceType, const OvString& fileLocation )
{
	OvResourceTicketSPtr	ticket = _reserve_ticket( resourceType, fileLocation );
	OvResourceSPtr resource = _find_loaded_resource( resourceType, fileLocation );
	if ( NULL == resource )
	{
		resource = LoadResource( resourceType, fileLocation );
		ticket->_check_in( resource.GetRear() );
	}
	return ticket;
}

OvResourceTicketSPtr OvResourceManager::AsyncLoadResource( const OvString& resourceType, const OvString& fileLocation )
{
	for each( const resource_loader_table::value_type& typevalue in m_loaderTable )
	{
		OvRTTI* rtti = const_cast<OvRTTI*>( typevalue.first );
		if ( rtti->TypeName() == resourceType )
		{
			return AsyncLoadResource( rtti, fileLocation );
		}
	}
	return NULL;
}

void OvResourceManager::ResourceCache( OvResourceSPtr resource )
{
	if ( resource )
	{
		if ( OvSTL_Find( m_cacheList, resource) == m_cacheList.end() )
		{
			m_cacheList.push_back( resource );
		}
	}
}
void OvResourceManager::_register_loaded_resource( const OvString& location, OvResource* resource )
{
	OvSectionGuardian guardian( m_load_section );
	SResourceInfo& info = m_resourceInfoTable[ location ];
	info.resource = resource;
	if ( info.ticket )
	{
		info.ticket->_check_in( resource );
	}
}

void OvResourceManager::_called_when_resource_created( OvResource* resource )
{
	OvSectionGuardian guardian( m_life_section );
	m_resourceList.push_back( resource );
}
void OvResourceManager::_called_when_resource_deleted( OvResource* resource )
{
	{
		OvSectionGuardian guardian( m_load_section );
		loaded_resource_table::iterator itor = m_resourceInfoTable.begin();
		for ( ; itor != m_resourceInfoTable.end() ; ++itor )
		{
			const SResourceInfo& info = itor->second;
			if ( resource == info.resource )
			{
				break;
			}
		}
		if ( itor != m_resourceInfoTable.end() )
		{
			SResourceInfo& info = itor->second;
			info.resource = NULL;
		}
	}
	OvSectionGuardian guardian( m_life_section );
	resource_list::iterator itor = std::find( m_resourceList.begin(), m_resourceList.end(), resource );
	if ( itor != m_resourceList.end() )
	{
		m_resourceList.erase( itor );
	}
}

void OvResourceManager::_called_when_ticket_created( OvResourceTicket* ticket )
{
	OvSectionGuardian guardian( m_load_section );
	SResourceInfo& info = m_resourceInfoTable[ ticket->GetFileName() ];
	info.ticket = ticket;
}

void OvResourceManager::_called_when_ticket_deleted( OvResourceTicket* ticket )
{
	OvSectionGuardian guardian( m_load_section );
	SResourceInfo& info = m_resourceInfoTable[ ticket->GetFileName() ];
	info.ticket = NULL;
}

OvResourceSPtr OvResourceManager::_find_loaded_resource( const OvRTTI* resourceType, const OvString& location )
{
	OvSectionGuardian guardian( m_load_section );
	OvResource* resource = NULL;
	loaded_resource_table::iterator itor = m_resourceInfoTable.find( location );
	if ( itor != m_resourceInfoTable.end() )
	{
		SResourceInfo& set = itor->second;
		resource =  set.resource;
	}
	return resource;
}

const OvString& OvResourceManager::FindFileLocation( OvResourceSPtr resource )
{
	static OvString empty = "";
	OvSectionGuardian guardian( m_load_section );
	loaded_resource_table::iterator itor = m_resourceInfoTable.begin();
	for ( ; itor != m_resourceInfoTable.end() ; ++itor )
	{
		const SResourceInfo& info = itor->second;
		if ( resource == info.resource )
		{
			return itor->first;
		}
	}
	return empty;
}

OvResourceTicketSPtr OvResourceManager::_reserve_ticket(  const OvRTTI* type, const OvString& fileLocation )
{
	if ( ! fileLocation.empty() )
	{
		loaded_resource_table::iterator itor;
		SResourceInfo info;
		{
			OvSectionGuardian guardian( m_load_section );
			info = m_resourceInfoTable[ fileLocation ];
			itor = m_resourceInfoTable.find( fileLocation );
		}
		if ( NULL == info.ticket )
		{
			info.ticket = OvNew OvResourceTicket( type, itor->first );
		}
		return info.ticket;
	}
	return NULL;
}

const OvString& OvResourceManager::ResourceDirectory()
{
	return m_resourceDirectory;
}

OvResourceTicketSPtr OvResourceManager::FindTicket( OvResourceSPtr resource )
{
	const OvString& file = FindFileLocation( resource );

	return _reserve_ticket( resource->QueryRTTI(), file );

}

OvResourceLoaderSPtr OvResourceManager::_find_resource_loader( const OvRTTI* resourceType )
{
	resource_loader_table::iterator itor = m_loaderTable.find( resourceType );
	if ( itor != m_loaderTable.end() )
	{
		return itor->second;
	}
	return NULL;
}

void OvResourceManager::_thread_routine( void* data )
{
	OvResourceManager* resource_manager = (OvResourceManager*)data;
	if ( resource_manager )
	{
		resource_manager->_async_routine();
	}
}

void OvResourceManager::_async_routine()
{
	while ( _get_async_life_flag() )
	{
		SAsyncLoadInfo info;
		if ( _pop_async_load_info( info ) )
		{
			OvResourceSPtr resource = NULL;
			if ( info.loader )
			{
				if ( resource = info.loader->_load_resource( info.file ) )
				{
					_register_loaded_resource( info.file, resource.GetRear() );
				}
			}
		}
	}
}

void OvResourceManager::_push_async_load_info( SAsyncLoadInfo& info )
{
	OvSectionGuardian guardian( m_load_section );
	m_aload_list.push_back( info );
}

OvBool OvResourceManager::_pop_async_load_info( SAsyncLoadInfo& info )
{
	OvSectionGuardian guardian( m_load_section );
	if ( m_aload_list.size() )
	{
		info = m_aload_list.front();
		m_aload_list.pop_front();
		return true;
	}
	return false;
}

struct SSection
{
	SSection()
	{
		::InitializeCriticalSection( &section );
	};
	~SSection()
	{
		::DeleteCriticalSection( &section );
	}
	CRITICAL_SECTION section;
};
OvBool& OvResourceManager::_get_async_life_flag()
{
	static SSection block;
	static OvBool life_flag(true);

	OvSectionGuardian guardian( block.section );
	return life_flag;
}
OvString AbsolutePath( const OvString& file )
{
	return OvResourceManager::GetInstance()->ResourceDirectory() + "\\" + file;
}

OvBool ClampPathIfResDir( OvString& file )
{
	OvString output;
	output = OvResourceManager::GetInstance()->ResourceDirectory() + "\\";
	if ( strncmp( output.c_str(), file.c_str(), output.size() ) == 0 )
	{
		file = &file.at( output.length() );
		return true;
	}
	return false;
}