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
	::DeleteCriticalSection( &m_load_section );
	m_cacheList.clear();
}

OvResourceSPtr OvResourceManager::LoadResource( const OvRTTI* resourceType, const string& fileLocation )
{
	OvResourceSPtr resource = NULL;
	resource = _find_loaded_resource( resourceType, fileLocation );
	if ( NULL == resource )
	{
		if ( OvResourceLoaderSPtr loader = _find_resource_loader( resourceType ) )
		{
			if ( resource = loader->_load_resource( fileLocation ) )
			{
				_register_loaded_resource( resource.GetRear(), fileLocation );
				return resource;
			}
		}
	}
	return resource;
}

OvResourceSPtr OvResourceManager::LoadResource( const string& resourceType, const string& fileLocation )
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
OvResourceTicketSPtr OvResourceManager::AsyncLoadResource( const OvRTTI* resourceType, const string& fileLocation )
{
	OvResourceTicketSPtr	ticket = _check_ticket( resourceType, fileLocation );
	OvResourceSPtr resource = _find_loaded_resource( resourceType, fileLocation );
	if ( NULL == resource )
	{
		SAsyncLoadInfo info;
		info.file = fileLocation;
		info.loader = _find_resource_loader( resourceType );
		info.loader = info.loader->Clone();
		_add_async_load_info( info );
	}
	return ticket;
}

OvResourceTicketSPtr OvResourceManager::AsyncLoadResource( const string& resourceType, const string& fileLocation )
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
void OvResourceManager::_register_loaded_resource( OvResource* resource, const string& location )
{
	_set_resource_location(resource, location);

	if ( OvResourceTicketSPtr ticket = _check_ticket( resource->QueryRTTI(), location ) )
	{
		ticket->_check_in( resource );
	}
}

void OvResourceManager::_called_when_resource_created( OvResource* resource )
{
	m_resourceLocationTable[ resource ] = "";
}
void OvResourceManager::_called_when_resource_deleted( OvResource* resource )
{
	resource_location_table::iterator itor = m_resourceLocationTable.find( resource );
	if ( m_resourceLocationTable.end() != itor )
	{
		m_resourceTicketTable.erase( itor->second );
		m_resourceLocationTable.erase( itor );
	}
}

void OvResourceManager::_called_when_ticket_created( OvResourceTicket* ticket )
{
	const string& file_location = ticket->GetFileName();

	if (
		! file_location.empty()
		&& 
		m_resourceTicketTable.find( file_location ) == m_resourceTicketTable.end() 
		)
	{
		m_resourceTicketTable[ file_location ] = ticket;
	}
}

void OvResourceManager::_called_when_ticket_deleted( OvResourceTicket* ticket )
{
	const string& file_location = ticket->GetFileName();
	m_resourceTicketTable.erase( file_location );
}

OvResourceSPtr OvResourceManager::_find_loaded_resource( const OvRTTI* resourceType, const string& location )
{
	for each( const resource_location_table::value_type& typevalue in m_resourceLocationTable)
	{
		OvResource* resource = typevalue.first;
		if ( resource->QueryRTTI() == resourceType )
		{
			if ( typevalue.second == location )
			{
				return resource;
			}
		}
	}
	return NULL;
}

string OvResourceManager::FindFileLocation( OvResourceSPtr resource )
{
	OvSectionGuardian guardian( m_load_section );
	string fileLocation = "";
	if ( resource )
	{
		resource_location_table::iterator itor = m_resourceLocationTable.find( resource.GetRear() );
		if ( m_resourceLocationTable.end() != itor )
		{
			fileLocation = itor->second;
		}
	}
	return fileLocation;
}

OvResourceTicketSPtr OvResourceManager::_check_ticket(  const OvRTTI* type, const string& fileLocation )
{
	OvSectionGuardian guardian( m_load_section );

	OvResourceTicketSPtr ticket = NULL;
	if ( ! fileLocation.empty() )
	{
		resource_ticket_table::iterator itor = m_resourceTicketTable.find( fileLocation );
		if ( itor == m_resourceTicketTable.end() )
		{
			ticket = OvNew OvResourceTicket( type, fileLocation );
		}
		else
		{
			ticket = itor->second;
		}
	}
	return ticket;
}

const string& OvResourceManager::ResourceDirectory()
{
	return m_resourceDirectory;
}

OvResourceTicketSPtr OvResourceManager::FindTicket( OvResourceSPtr resource )
{
	const string& file = FindFileLocation( resource );

	return _check_ticket( resource->QueryRTTI(), file );

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
		async_load_list copy_list;
		_copy_async_load_list( copy_list );
		OvResourceSPtr resource = NULL;
		for each( SAsyncLoadInfo info in copy_list )
		{
			if ( info.loader )
			{
				if ( resource = info.loader->_load_resource( info.file ) )
				{
					_register_loaded_resource( resource.GetRear(), info.file );
				}
			}
		}
		_clear_async_load_list();
	}
}

void OvResourceManager::_add_async_load_info( SAsyncLoadInfo& info )
{
	OvSectionGuardian guardian( m_load_section );
	m_aload_list.push_back( info );
}

void OvResourceManager::_copy_async_load_list( async_load_list& copy )
{
	OvSectionGuardian guardian( m_load_section );
	copy = m_aload_list;
}

void OvResourceManager::_clear_async_load_list()
{
	OvSectionGuardian guardian( m_load_section );
	m_aload_list.clear();
}

void OvResourceManager::_set_resource_location( OvResource* resource, const string& location )
{
	OvSectionGuardian guardian( m_load_section );
	resource_location_table::iterator itor = m_resourceLocationTable.find( resource );
	if ( m_resourceLocationTable.end() != itor )
	{
		itor->second = location;
	}
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
bool& OvResourceManager::_get_async_life_flag()
{
	static SSection block;
	static bool life_flag(true);

	OvSectionGuardian guardian( block.section );
	return life_flag;
}
std::string ResDirPath( const std::string& file )
{
	return OvResourceManager::GetInstance()->ResourceDirectory() + "\\" + file;
}

bool ClampPathIfResDir( std::string& file )
{
	string output;
	output = OvResourceManager::GetInstance()->ResourceDirectory() + "\\";
	if ( strncmp( output.c_str(), file.c_str(), output.size() ) == 0 )
	{
		file = &file.at( output.length() );
		return true;
	}
	return false;
}