#pragma once
#include "OvRefBase.h"
#include "OvAutoPtr.h"
//
//OvREF_POINTER(OvTexture);
//OvREF_POINTER(OvMesh);
//

OvREF_POINTER(OvVertexShader);
OvREF_POINTER(OvPixelShader);
OvREF_POINTER(OvRenderableObject);
OvREF_POINTER(OvTexture);

OvREF_POINTER(OvMaterial);
class OvMaterial : public OvRefBase
{
public:

	OvMaterial();
	~OvMaterial();

	void	SetVertexShader(OvVertexShaderSPtr pVertShader);
	OvVertexShaderSPtr GetVertexShader();

	void	SetPixelShader(OvPixelShaderSPtr pPixShader);
	OvPixelShaderSPtr GetPixelShader();

	void	ApplyMaterial(OvRenderableObjectSPtr,void* pUserExtraData = NULL);
	void	PrepareShader(OvRenderableObjectSPtr, OvVertexShaderSPtr, OvPixelShaderSPtr, void* pUserExtraData);

	void	SetDiffuseTexture(OvTextureSPtr pTesture);
	OvTextureSPtr GetDiffuseTexture();

	void	SetSpecularMaskTexture(OvTextureSPtr pTesture);
	OvTextureSPtr	GetSpecularMaskTexture();

private:
	struct OvPimple;
	OvAutoPtr< OvPimple> m_pPimple;
};
