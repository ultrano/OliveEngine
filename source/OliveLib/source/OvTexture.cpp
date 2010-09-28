#include "OvTexture.h"
#include "OvRenderer.h"
#include <d3dx9.h>

OvRTTI_IMPL(OvTexture);

OvTexture::OvTexture()
{
};

OvTexture::OvTexture( LPDIRECT3DTEXTURE9 texture )
: m_texture( texture )
{

}
OvTexture::~OvTexture()
{
	if ( m_texture )
	{
		m_texture->Release();
	}
};
LPDIRECT3DTEXTURE9 OvTexture::ToDxTexture()
{
	return m_texture;
}

LPDIRECT3DSURFACE9 OvTexture::GetSurface( unsigned level /*= 0 */ )
{
	LPDIRECT3DSURFACE9 surface = NULL;
	if ( m_texture )
	{
		if ( m_texture->GetLevelCount() )
		{
			m_texture->GetSurfaceLevel( level, &surface );
		}
	}
	return surface;
}

bool SaveTexture( const std::string& file, OvTextureSPtr texture, D3DXIMAGE_FILEFORMAT format )
{
	HRESULT hr = D3DXSaveTextureToFile( file.c_str(), format, texture->ToDxTexture() ,NULL);
	return SUCCEEDED( hr );
}