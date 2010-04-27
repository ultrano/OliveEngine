#include "OvShaderManager.h"
#include "OvShaderConstantTable.h"
#include "OvRenderer.h"
#include "OvTransform.h"
#include "OvStringUtility.h"
#include "OvTexture.h"
#include <d3dx9.h>
#include <map>

OvSingletonEx_IMPL(OvShaderManager);

void OvShaderManager::Singleton_InitializeProcessing()
{

}
void OvShaderManager::Singleton_TerminateProcessing()
{

}

bool	OvShaderManager::SetVSConstB(const OvShaderConstInfo& rConstInfo,bool bCheck)
{
	LPDIRECT3DDEVICE9 kpDevice =  (LPDIRECT3DDEVICE9)OvRenderer::GetInstance()->GetDevice();
	if (kpDevice)
	{
		HRESULT kHs = E_FAIL;
		kHs = kpDevice->SetVertexShaderConstantB(rConstInfo.RegistIndex,(const BOOL *)&bCheck,rConstInfo.ConstCount);
		return SUCCEEDED(kHs);
	}
	return false;
}
bool	OvShaderManager::GetVSConstB(const OvShaderConstInfo& rConstInfo,bool& bCheck)
{
	LPDIRECT3DDEVICE9 kpDevice =  (LPDIRECT3DDEVICE9)OvRenderer::GetInstance()->GetDevice();
	if (kpDevice)
	{
		HRESULT kHs = E_FAIL;
		kHs = kpDevice->GetVertexShaderConstantB(rConstInfo.RegistIndex,(BOOL *)&bCheck,rConstInfo.ConstCount);
		return SUCCEEDED(kHs);
	}
	return false;
}

bool	OvShaderManager::SetVSConstF(const OvShaderConstInfo& rConstInfo,float* pConst,size_t stConstSize)
{
	LPDIRECT3DDEVICE9 kpDevice =  (LPDIRECT3DDEVICE9)OvRenderer::GetInstance()->GetDevice();
	if (kpDevice)
	{
		HRESULT kHs = E_FAIL;
		kHs = kpDevice->SetVertexShaderConstantF(rConstInfo.RegistIndex,(float*)pConst,rConstInfo.ConstCount);

		//! byte���� ���� �ּҴ����� �ǹ̿��� �����ָ� ����μ� 1���̴� �ǹ̾��⵵ �ϴ�.
		/*UINT uiRegConstSize = kConstInfo.ConstCount * sizeof(float) * 4 * sizeof(byte);
		if (stConstSize <= uiRegConstSize)
		{
		}
		else
		{
			OvFormatString kErrMsg("�Ծ�� ����� ���� Ů�ϴ�.\n�Ծ�� ũ��: %d byte\n��û�� ũ��: %d byte",uiRegConstSize,stConstSize);
			OvAssertMsg(kErrMsg);
		}*/
		return SUCCEEDED(kHs);
	}
	return false;
}
bool	OvShaderManager::GetVSConstF(const OvShaderConstInfo& rConstInfo,float* pConst,size_t stConstSize)
{
	LPDIRECT3DDEVICE9 kpDevice =  (LPDIRECT3DDEVICE9)OvRenderer::GetInstance()->GetDevice();
	if (kpDevice)
	{
		HRESULT kHs = E_FAIL;
		kHs = kpDevice->GetVertexShaderConstantF(rConstInfo.RegistIndex,(float*)pConst,rConstInfo.ConstCount);

		//! byte���� ���� �ּҴ����� �ǹ̿��� �����ָ� ����μ� 1���̴� �ǹ̾��⵵ �ϴ�.
		/*UINT uiRegConstSize = kConstInfo.ConstCount * sizeof(float) * 4 * sizeof(byte);
		if (stConstSize >= uiRegConstSize)
		{
		}
		else
		{
			OvFormatString kErrMsg("�Ծ�� ����� ���� �۽��ϴ�.\n�Ծ�� ũ��: %d byte\n��û�� ũ��: %d byte",uiRegConstSize,stConstSize);
			OvAssertMsg(kErrMsg);
		}*/
		return SUCCEEDED(kHs);
	}
	return false;
}
bool	OvShaderManager::SetVSConst(const OvShaderConstInfo& rConstInfo,const OvMatrix& rType)
{
	OvMatrix kMat;
	kMat = OvMatrixTranspose(rType);
	return SetVSConstF(rConstInfo,(float*)&(kMat),sizeof(OvMatrix));
}
bool	OvShaderManager::GetVSConst(const OvShaderConstInfo& rConstInfo,OvMatrix& rType)
{
	OvMatrix kMat;
	if (GetVSConstF(rConstInfo,(float*)&(kMat),sizeof(OvMatrix)))
	{
		rType = OvMatrixTranspose(kMat);
		return true;
	}
	return false;
}
//////////////////////////////////////

bool	OvShaderManager::SetPSConstF(const OvShaderConstInfo& rConstInfo,float* pConst,size_t stConstSize)
{
	LPDIRECT3DDEVICE9 kpDevice =  (LPDIRECT3DDEVICE9)OvRenderer::GetInstance()->GetDevice();
	if (kpDevice)
	{
		HRESULT kHs = E_FAIL;
		kHs = kpDevice->SetPixelShaderConstantF(rConstInfo.RegistIndex,(float*)pConst,rConstInfo.ConstCount);
		return SUCCEEDED(kHs);
	}
	return false;

}
bool	OvShaderManager::GetPSConstF(const OvShaderConstInfo& rConstInfo,float* pConst,size_t stConstSize)
{
	LPDIRECT3DDEVICE9 kpDevice =  (LPDIRECT3DDEVICE9)OvRenderer::GetInstance()->GetDevice();
	if (kpDevice)
	{
		HRESULT kHs = E_FAIL;
		kHs = kpDevice->SetPixelShaderConstantF(rConstInfo.RegistIndex,(float*)pConst,rConstInfo.ConstCount);
		return SUCCEEDED(kHs);
	}
	return false;

}
bool	OvShaderManager::SetTexture(UINT uiSamplerIndex,OvTextureSPtr pTexture)
{
	LPDIRECT3DDEVICE9 kpDevice =  (LPDIRECT3DDEVICE9)OvRenderer::GetInstance()->GetDevice();
	if (kpDevice && pTexture)
	{
		HRESULT kHs = E_FAIL;
		kHs = kpDevice->SetTexture(uiSamplerIndex,(LPDIRECT3DTEXTURE9)pTexture->GetTexture());
		return SUCCEEDED(kHs);
	}
	return false;
}
////////////////////////////////////////////////////////////////////////////////////
////////////////////////////////////////////////////////////////////////////////////


OvShaderConstInfo::OvShaderConstInfo()
:ArrayCount(1)
,RegistIndex(0)
,ConstCount(0)
{};
OvShaderConstInfo::OvShaderConstInfo(const string& T, const string& N, UINT R,UINT C)
:ArrayCount(1)
,Type(T)
,Name(N)
,RegistIndex(R)
,ConstCount(C)
{};
OvShaderConstInfo::OvShaderConstInfo(UINT A, const string& T, const string& N, UINT R,UINT C)
:ArrayCount(A)
,Type(T)
,Name(N)
,RegistIndex(R)
,ConstCount(C)
{

}
OvShaderConstInfo OvShaderConstInfo::operator[](const UINT uiIndex)const
{
	UINT kuiAccess = uiIndex;
	if (uiIndex>=ArrayCount)
	{
		OvFormatString kErrMsg(
			"�Ծ�� ���̴� ��� �迭 ũ�⸦ ������ϴ�.\n"
			"���� ��� �ε���: 0~%d \n"
			"���� ��û�� �ε���: %d ",ArrayCount-1,uiIndex);
		OvAssertMsg(kErrMsg);
		kuiAccess = ArrayCount;
	}
	return OvShaderConstInfo(Type,Name,RegistIndex+(ConstCount*uiIndex),ConstCount);
}