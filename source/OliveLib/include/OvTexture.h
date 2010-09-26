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

