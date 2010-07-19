#pragma once
#include "OvShader.h"

OvREF_POINTER(OvPixelShader);
class OvPixelShader : public OvShader
{
	OvRTTI_DECL(OvPixelShader);
public:

	OvPixelShader( LPDIRECT3DPIXELSHADER9 pixelShader );
	~OvPixelShader();

	LPDIRECT3DPIXELSHADER9 ToDirectShader();

private:

	LPDIRECT3DPIXELSHADER9 m_pixelShader;
};