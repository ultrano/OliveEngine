#include "OvResourceManager.h"
#include "OvFileMeshLoader.h"
#include "OvTextureLoader.h"
#include "OvShaderCodeLoader.h"
#include "OvMaterialLoader.h"

#include <algorithm>

OvResourceManager::OvResourceManager()
{
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

}

OvResourceManager::~OvResourceManager()
{
	m_cacheList.clear();
}

OvResourceSPtr OvResourceManager::LoadResource( const OvRTTI* resourceType, const string& fileLocation )
{
	OvResourceSPtr resource = NULL;
	resource = _find_loaded_resource( resourceType, fileLocation );
	if ( NULL == resource )
	{
		return _force_load_resouroce( resourceType, fileLocation );
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

OvResourceSPtr OvResourceManager::ReloadResource( const string& fileLocation )
{
	for each( const resource_location_table::value_type& table_pair in m_resourceLocationTable )
	{
		if ( fileLocation == table_pair.second )
		{
			return ReloadResource( table_pair.first );
		}
	}
	return NULL;
}

OvResourceSPtr OvResourceManager::ReloadResource( OvResourceSPtr resource )
{
	if ( resource )
	{
		std::string fileLocation = FindFileLocation( resource );
		const OvRTTI* resourceType = resource->QueryRTTI();
		if ( !fileLocation.empty() && resourceType )
		{
			m_resourceLocationTable.erase( resource.GetRear() );
			resource = _force_load_resouroce( resourceType, fileLocation );

			OvResourceTicketSPtr ticket = NULL;
			resource_ticket_table::iterator itor = m_resourceTicketTable.find( fileLocation );
			if ( itor != m_resourceTicketTable.end() )
			{
				if ( OvResourceTicket* ticket = itor->second )
				{
					ticket->_called_when_resource_reloaded( resource.GetRear() );
				}
			}
		}
	}
	return resource;
}
void OvResourceManager::ReloadResourceAll()
{
	vector< OvResourceSPtr > res_holder;
	res_holder.reserve( m_resourceLocationTable.size() );

	for each ( resource_location_table::value_type table_value in m_resourceLocationTable )
	{
		res_holder.push_back( table_value.first );
	}

	for each ( OvResourceSPtr resource in res_holder )
	{
		ReloadResource( resource );
	}

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
	resource_location_table::iterator itor = m_resourceLocationTable.find( resource );
	if ( m_resourceLocationTable.end() != itor )
	{
		itor->second = location;
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
	const string& file_location = FindFileLocation( ticket->m_resource.GetRear() );
	if ( ! file_location.empty() )
	{
		m_resourceTicketTable[ file_location ] = ticket;
	}
}

void OvResourceManager::_called_when_ticket_deleted( OvResourceTicket* ticket )
{
	const string& file_location = FindFileLocation( ticket->m_resource );
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

OvResourceTicketSPtr OvResourceManager::CheckIn( OvResourceSPtr resource )
{
	if ( resource )
	{
		string location = FindFileLocation( resource );
		resource_ticket_table::iterator itor = m_resourceTicketTable.find( location );
		if ( itor != m_resourceTicketTable.end() )
		{
			return itor->second;
		}

		return ( OvNew OvResourceTicket( resource.GetRear() ) );
	}
	return NULL;
}

OvResourceSPtr OvResourceManager::_force_load_resouroce( const OvRTTI* resourceType, const string& fileLocation )
{
	OvResourceSPtr resource = NULL;
	for each( const resource_loader_table::value_type& typevalue in m_loaderTable )
	{
		if ( typevalue.first == resourceType )
		{
			OvResourceLoaderSPtr loader = typevalue.second;
			if ( loader )
			{
				if ( resource = loader->_load_resource( fileLocation ) )
				{
					_register_loaded_resource( resource.GetRear(), fileLocation );
					return resource;
				}
			}
		}
	}
	return resource;
}

const string& OvResourceManager::ResourceDirectory()
{
	return m_resourceDirectory;
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