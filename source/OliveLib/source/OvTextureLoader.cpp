#include "OvTextureLoader.h"
#include "OvTexture.h"
#include "OvRenderer.h"

OvRTTI_IMPL( OvTextureLoader );

OvResourceSPtr OvTextureLoader::Load( const std::string& fileLocation )
{
	if ( fileLocation.empty() == false )
	{
		OvDevice device = OvRenderer::GetInstance()->GetDevice();
		if ( device )
		{
			LPDIRECT3DTEXTURE9	kpTexture = NULL;
			if ( SUCCEEDED( D3DXCreateTextureFromFile( device, fileLocation.c_str(), &kpTexture ) ) )
			{
				OvTextureSPtr texture = OvNew OvTexture;
				texture->m_texture = kpTexture;
				return texture;
			}
		}
	}
	return NULL;
}
