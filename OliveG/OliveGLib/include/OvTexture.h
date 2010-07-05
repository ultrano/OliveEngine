#pragma once

#include "OvResource.h"
#include "OvAutoPtr.h"
#include "OvUtility.h"
#include "OvRenderingCommon.h"

OvREF_POINTER(OvTexture)

class OvTexture : public OvResource
{
	OvRTTI_DECL(OvTexture);
public:
	OvTexture();
	~OvTexture();

	LPDIRECT3DTEXTURE9 ToDxTexture();

	virtual bool	Load( const std::string& fileLocation ) override;

private:
	LPDIRECT3DTEXTURE9 m_texture;
};