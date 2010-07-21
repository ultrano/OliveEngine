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
	m_loaderTable[ OvShaderCode		::GetRTTI() ]	= OvNew OvShaderCodeLoader;
	m_loaderTable[ OvMaterial		::GetRTTI() ]	= OvNew OvMaterialLoader;
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
					}
					return resource;
				}
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
	resource_table::iterator itor = m_resourceTable.find( resource );
	if ( m_resourceTable.end() != itor )
	{
		itor->second = location;
	}
}

void OvResourceManager::_resource_created( OvResource* resource )
{
	m_resourceTable[ resource ] = "";
}
void OvResourceManager::_resource_deleted( OvResource* resource )
{
	m_resourceTable.erase( resource );
}

OvResourceSPtr OvResourceManager::_find_loaded_resource( const OvRTTI* resourceType, const string& location )
{
	for each( const resource_table::value_type& typevalue in m_resourceTable)
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

string OvResourceManager::FindFileLocation( OvResource* resource )
{
	string fileLocation = "";
	resource_table::iterator itor = m_resourceTable.find( resource );
	if ( m_resourceTable.end() != itor )
	{
		fileLocation = itor->second;
	}
	return fileLocation;
}