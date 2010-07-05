#include "OvTexture.h"
#include "OvRenderer.h"
#include <d3dx9.h>

OvRTTI_IMPL(OvTexture);

OvTexture::OvTexture()
{
};
OvTexture::~OvTexture()
{
};
LPDIRECT3DTEXTURE9 OvTexture::ToDxTexture()
{
	return m_texture;
}
bool	OvTexture::Load( const std::string& fileLocation )
{
	if ( fileLocation.empty() == false )
	{
		LPDIRECT3DDEVICE9 device = OvRenderer::GetInstance()->GetDevice();
		if ( device )
		{
			LPDIRECT3DTEXTURE9	kpTexture = NULL;
			if ( SUCCEEDED( D3DXCreateTextureFromFile( device, fileLocation.c_str(), &kpTexture ) ) )
			{
				return kpTexture;
			}
		}
	}
	return false;
}