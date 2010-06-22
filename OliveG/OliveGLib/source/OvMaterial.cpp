#include "OvMaterial.h"
#include "OvTexture.h"
#include "OvRenderer.h"
#include "OvMaterialManager.h"
#include "OvRenderableObject.h"
#include "OvVertexShader.h"
#include "OvPixelShader.h"
#include "OvTransform.h"
#include <map>
#include <d3dx9.h>

struct OvMaterial::OvPimple : OvMemObject
{
	OvVertexShaderSPtr	m_pVertShader;
	OvPixelShaderSPtr	m_pPixShader;
	OvTextureSPtr		m_pDiffuseTex;
	OvTextureSPtr		m_pSpecMaskTex;
};

OvMaterial::OvMaterial()
:m_pPimple(OvNew OvMaterial::OvPimple)
{
}
OvMaterial::~OvMaterial()
{

}

void	OvMaterial::SetVertexShader(OvVertexShaderSPtr pVertShader)
{
	m_pPimple->m_pVertShader = pVertShader;
}
OvVertexShaderSPtr OvMaterial::GetVertexShader()
{
	return m_pPimple->m_pVertShader;
}
void	OvMaterial::SetPixelShader(OvPixelShaderSPtr pPixShader)
{
	m_pPimple->m_pPixShader = pPixShader;
}
OvPixelShaderSPtr OvMaterial::GetPixelShader()
{
	return m_pPimple->m_pPixShader;
}
void	OvMaterial::ApplyMaterial(OvRenderableObjectSPtr pRO,void* pUserExtraData /*= NULL*/)
{
	OvVertexShaderSPtr	pVS = GetVertexShader();
	OvPixelShaderSPtr	pPS = GetPixelShader();

	if (pRO && pVS && pPS)
	{
		if (pVS->Activate() && pPS->Activate())
		{
			PrepareShader( pRO,  pVS,  pPS,  pUserExtraData);
		}
	}
}
void	OvMaterial::PrepareShader(OvRenderableObjectSPtr pRO, OvVertexShaderSPtr pVS, OvPixelShaderSPtr pPS, void* pUserExtraData)
{
	OvShaderConstantTableSPtr pVSConstTable = pVS->GetConstantTable();
	OvShaderConstantTableSPtr pPSConstTable = pPS->GetConstantTable();

	OvMatrix kMat;

	OvShaderManager::GetInstance()->GetVSConst(OvMaterialVSConstTable::Matrix_ViewProject,kMat);

	kMat = pRO->GetWorldMatrix()*kMat;

	OvShaderManager::GetInstance()->SetVSConst(OvMaterialVSConstTable::Float4x3_World,pRO->GetWorldMatrix());
	OvShaderManager::GetInstance()->SetVSConst(OvMaterialVSConstTable::Matrix_WorldViewProject,kMat);

	OvShaderManager::GetInstance()->SetTexture(0,GetDiffuseTexture());
	OvShaderManager::GetInstance()->SetTexture(1,GetSpecularMaskTexture());

}
void	OvMaterial::SetDiffuseTexture(OvTextureSPtr pTesture)
{
	m_pPimple->m_pDiffuseTex = pTesture;
}
OvTextureSPtr OvMaterial::GetDiffuseTexture()
{
	return m_pPimple->m_pDiffuseTex;
}
void	OvMaterial::SetSpecularMaskTexture(OvTextureSPtr pTesture)
{
	m_pPimple->m_pSpecMaskTex = pTesture;
}
OvTextureSPtr	OvMaterial::GetSpecularMaskTexture()
{
	return m_pPimple->m_pSpecMaskTex;
}