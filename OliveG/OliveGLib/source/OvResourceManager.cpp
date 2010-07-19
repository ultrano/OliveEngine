#include "OvResourceManager.h"
#include "OvFileMeshLoader.h"
#include "OvTextureLoader.h"
#include "OvPixelShaderLoader.h"
#include "OvVertexShaderLoader.h"

OvResourceManager::OvResourceManager()
{
	m_loaderTable[ OvMesh::GetRTTI() ] = OvNew OvFileMeshLoader;
	m_loaderTable[ OvTexture::GetRTTI() ] = OvNew OvTextureLoader;
	m_loaderTable[ OvPixelShader::GetRTTI() ] = OvNew OvPixelShaderLoader;
	m_loaderTable[ OvVertexShader::GetRTTI() ] = OvNew OvVertexShaderLoader;

}

OvResourceManager::~OvResourceManager()
{

}

OvResourceSPtr OvResourceManager::LoadResource( const OvRTTI* resourceType, const string& fileLocation )
{
	if ( resourceType )
	{
		return LoadResource( const_cast<OvRTTI*>(resourceType)->TypeName(), fileLocation );
	}
}

OvResourceSPtr OvResourceManager::LoadResource( const string& resourceType, const string& fileLocation )
{
	OvResourceSPtr resource = NULL;
	resource = _find_loaded_resource( fileLocation );
	if (  NULL == resource )
	{
		for each( resource_loader_table::value_type tableIter in m_loaderTable )
		{
			OvRTTI* rtti = const_cast<OvRTTI*>( tableIter.first );
			if ( rtti->TypeName() == resourceType )
			{
				OvResourceLoaderSPtr loader = tableIter.second;
				if ( loader )
				{
					if ( resource = loader->Load( fileLocation ) )
					{
						resource->SetFileLocation( fileLocation );
						_register_resource( fileLocation, resource.GetRear() );
					}
					return resource;
				}
			}
		}
	}
	return resource;
}

void OvResourceManager::_register_resource( const string& location, OvResource* resource )
{
	if ( m_resourceTable.find( location ) == m_resourceTable.end() )
	{
		m_resourceTable[ location ] = resource;
	}
}
void OvResourceManager::_resource_deleted( OvResource* resource )
{
	string location;
	for each( resource_table::value_type res in m_resourceTable)
	{
		if ( res.second == resource )
		{
			location = res.first;
		}
	}
	m_resourceTable.erase( location );
}

OvResourceSPtr OvResourceManager::_find_loaded_resource( const string& location )
{
	resource_table::iterator findIter = m_resourceTable.find( location );
	if ( findIter != m_resourceTable.end() )
	{
		OvResourceSPtr resource = findIter->second;
		return resource;
	}
	return NULL;
}
