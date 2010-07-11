#include "OvTextureLoader.h"
#include "OvRenderer.h"

OvResourceSPtr OvTextureLoader::Load( const std::string& fileLocation )
{
	if ( fileLocation.empty() == false )
	{
		LPDIRECT3DDEVICE9 device = OvRenderer::GetInstance()->GetDevice();
		if ( device )
		{
			LPDIRECT3DTEXTURE9	kpTexture = NULL;
			if ( SUCCEEDED( D3DXCreateTextureFromFile( device, fileLocation.c_str(), &kpTexture ) ) )
			{
				OvTextureSPtr texture = new OvTexture;
				texture->m_texture = kpTexture;
				return texture;
			}
		}
	}
	return NULL;
}
