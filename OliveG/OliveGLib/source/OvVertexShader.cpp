#include "OvVertexShader.h"
#include "OvRenderer.h"
#include "d3dx9.h"
OvRTTI_IMPL(OvVertexShader);

OvVertexShader::OvVertexShader( LPDIRECT3DVERTEXSHADER9 vertexShader )
: m_vertexShader( vertexShader )
{

}

OvVertexShader::~OvVertexShader()
{
	if ( m_vertexShader )
	{
		m_vertexShader->Release();
	}
}

LPDIRECT3DVERTEXSHADER9 OvVertexShader::ToDirectShader()
{
	return m_vertexShader;
}