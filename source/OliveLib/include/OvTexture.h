#pragma once

#include "OvResource.h"
#include "OvAutoPtr.h"
#include "OvUtility.h"
#include "OvRenderingCommon.h"

OvREF_POINTER(OvTexture)

enum eTexUsage
{
	eTexUsage_Texture,
	eTexUsage_RenderTarget,
	eTexUsage_DepthStencil,
	eTexUsage_Unknown,
};

class OvTexture : public OvResource
{
	OvRTTI_DECL(OvTexture);
	friend class OvTextureLoader;
public:
public:

	OvTexture();
	OvTexture( LPDIRECT3DTEXTURE9 texture, eTexUsage usage );
	~OvTexture();

	LPDIRECT3DTEXTURE9 ToDxTexture();
	LPDIRECT3DSURFACE9 GetSurface( unsigned level = 0 );
	eTexUsage	UsageType();

private:
	LPDIRECT3DTEXTURE9 m_texture;
	eTexUsage m_usage;
};

OvREF_POINTER(OvCubeTexture)

class OvCubeTexture : public OvResource
{
	OvRTTI_DECL(OvCubeTexture);
public:

	OvCubeTexture();
	OvCubeTexture( LPDIRECT3DCUBETEXTURE9 cube_texture, eTexUsage usage );
	~OvCubeTexture();

	LPDIRECT3DCUBETEXTURE9 ToDxCubeTexture();
	LPDIRECT3DSURFACE9 GetCubeSurface( D3DCUBEMAP_FACES face_index, unsigned level = 0 );
	eTexUsage	UsageType();

private:
	LPDIRECT3DCUBETEXTURE9 m_cube_texture;
	eTexUsage m_usage;
};

bool SaveTexture( const OvString& file, OvTextureSPtr texture, D3DXIMAGE_FILEFORMAT format);
