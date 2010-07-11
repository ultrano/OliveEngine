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
	~OvTexture();

	LPDIRECT3DTEXTURE9 ToDxTexture();

private:
	LPDIRECT3DTEXTURE9 m_texture;
};