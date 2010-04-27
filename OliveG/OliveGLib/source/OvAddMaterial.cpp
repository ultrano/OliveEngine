//#include "OvAddMaterial.h"
//#include <d3dx9.h>
//OvAddMaterial::OvAddMaterial()
//:m_fTime(0)
//,m_fInterval(1)
//{
//
//}
//void OvAddMaterial::PrepareOutput()
//{
//	m_fTime += 0.01f*m_fInterval;
//	if (m_fTime>=1.0f || m_fTime <=0)
//	{
//		m_fInterval *= -1;
//	}
//
//	LPD3DXEFFECT kpShader = (LPD3DXEFFECT)GetShader();
//	if (kpShader)
//	{
//		kpShader->SetFloat("f1",m_fTime);
//	}
//}