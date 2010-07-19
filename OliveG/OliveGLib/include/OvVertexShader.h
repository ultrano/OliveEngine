#pragma once
#include "OvShader.h"

OvREF_POINTER(OvVertexShader);
class OvVertexShader : public OvShader
{
	OvRTTI_DECL(OvVertexShader);
public:

	OvVertexShader( LPDIRECT3DVERTEXSHADER9 vertexShader );
	~OvVertexShader();

	LPDIRECT3DVERTEXSHADER9 ToDirectShader();

private:

	LPDIRECT3DVERTEXSHADER9 m_vertexShader;

};
