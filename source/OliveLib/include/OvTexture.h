#pragma once

#include "OvResource.h"
#include "OvAutoPtr.h"
#include "OvUtility.h"
#include "OvRenderingCommon.h"

OvREF_POINTER(OvTexture)

class OvTexture : public OvResource
{
	OvRTTI_DECL(OvTexture);
	friend class OvTextureLoader;
public:

	OvTexture();
	OvTexture( LPDIRECT3DTEXTURE9 texture );
	~OvTexture();

	LPDIRECT3DTEXTURE9 ToDxTexture();
	LPDIRECT3DSURFACE9 GetSurface( unsigned level = 0 );

private:
	LPDIRECT3DTEXTURE9 m_texture;
};

OvREF_POINTER(OvCubeTexture)

class OvCubeTexture : public OvResource
{
	OvRTTI_DECL(OvCubeTexture);
public:

	OvCubeTexture();
	OvCubeTexture( LPDIRECT3DCUBETEXTURE9 cube_texture );
	~OvCubeTexture();

	LPDIRECT3DCUBETEXTURE9 ToDxCubeTexture();
	LPDIRECT3DSURFACE9 GetCubeSurface( D3DCUBEMAP_FACES face_index, unsigned level = 0 );

private:
	LPDIRECT3DCUBETEXTURE9 m_cube_texture;
};

bool SaveTexture( const std::string& file, OvTextureSPtr texture, D3DXIMAGE_FILEFORMAT format);