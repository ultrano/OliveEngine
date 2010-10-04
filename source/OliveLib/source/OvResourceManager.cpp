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
	GetModuleFileName( NULL, (LPCH)m_resourceDirectory.c_str(), m_resourceDirectory.size() );

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
	OvResourceSPtr resource = NULL;

	for each( const resource_location_table::value_type& table_pair in m_resourceLocationTable )
	{
		if ( fileLocation == table_pair.second )
		{
			resource = table_pair.first;
			break;
		}
	}

	if ( resource )
	{
		const OvRTTI* resourceType = resource->QueryRTTI();
		if ( resourceType )
		{
			m_resourceLocationTable.erase( resource.GetRear() );
			resource = _force_load_resouroce( resourceType, fileLocation );

			OvResourceTicketSPtr ticket = NULL;
			resource_ticket_table::iterator itor = m_resourceTicketTable.find( fileLocation );
			if ( itor != m_resourceTicketTable.end() )
			{
				resource_ticket_table::referent_type& ticket_list = itor->second;
				for each( OvResourceTicket* ticket in ticket_list )
				{
					ticket->_called_when_resource_reloaded( resource.GetRear() );
				}
			}
		}
	}
	return resource;
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
		resource_ticket_table::referent_type& ticket_list = m_resourceTicketTable[ file_location ];
		ticket_list.push_back( ticket );
	}
}

void OvResourceManager::_called_when_ticket_deleted( OvResourceTicket* ticket )
{
	const string& file_location = FindFileLocation( ticket->m_resource );
	resource_ticket_table::iterator itor = m_resourceTicketTable.find( file_location );
	if ( itor != m_resourceTicketTable.end() )
	{
		resource_ticket_table::referent_type& ticket_list = itor->second;
		resource_ticket_table::referent_type::iterator found_itor = find( ticket_list.begin(), ticket_list.end(), ticket );
		if ( found_itor != ticket_list.end() )
		{
			ticket_list.erase( found_itor );
		}
	}
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
	resource_location_table::iterator itor = m_resourceLocationTable.find( resource.GetRear() );
	if ( m_resourceLocationTable.end() != itor )
	{
		fileLocation = itor->second;
	}
	return fileLocation;
}

OvResourceTicketSPtr OvResourceManager::CheckIn( OvResourceSPtr resource )
{
	OvResourceTicketSPtr ticket = NULL;
	ticket = OvNew OvResourceTicket( resource.GetRear() );
	return ticket;
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