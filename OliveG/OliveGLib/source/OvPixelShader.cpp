#include "OvPixelShader.h"
#include "OvRenderer.h"
#include "d3dx9.h"
OvRTTI_IMPL(OvPixelShader);

OvPixelShader::OvPixelShader( LPDIRECT3DPIXELSHADER9 pixelShader )
: m_pixelShader( pixelShader )
{

}

OvPixelShader::~OvPixelShader()
{
	if ( m_pixelShader )
	{
		m_pixelShader->Release();
	}
}

LPDIRECT3DPIXELSHADER9 OvPixelShader::ToDirectShader()
{
	return m_pixelShader;
}