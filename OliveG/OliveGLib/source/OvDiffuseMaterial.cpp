//#include "OvDiffuseMaterial.h"
//#include "OvTexture.h"
//#include <d3dx9.h>
//struct OvDiffuseMaterial::OvPimple : OvMemObject
//{
//	OvTextureSPtr	mDiffuseTexture;
//};
//
//OvDiffuseMaterial::OvDiffuseMaterial()
//:m_pPimple(new OvDiffuseMaterial::OvPimple)
//{
//
//}
//OvDiffuseMaterial::~OvDiffuseMaterial()
//{
//
//}
//void	OvDiffuseMaterial::SetDiffuseTexture(OvTextureSPtr pTexture)
//{
//	m_pPimple->mDiffuseTexture = pTexture;
//}
//
//void	OvDiffuseMaterial::PrepareOutput()
//{
//	LPD3DXEFFECT kpShader = (LPD3DXEFFECT)GetShader();
//	if (kpShader)
//	{
//		if (m_pPimple->mDiffuseTexture)
//		{
//			kpShader->SetTexture("TEX_DIFFUSE",(LPDIRECT3DTEXTURE9)m_pPimple->mDiffuseTexture->GetTexture());
//		}
//	}
//}