#include "OvShaderManager.h"
#include "OvRenderer.h"
#include "OvResourceManager.h"
#include "OvShaderCode.h"
#include "OvTransform.h"
#include "OvStringUtility.h"
#include "OvVertexShader.h"
#include "OvPixelShader.h"
#include "OvTexture.h"
#include <d3dx9.h>
#include <map>

OvShaderManager::OvShaderManager()
{
}
OvShaderManager::~OvShaderManager()
{

}


OvBool	OvShaderManager::SetVSConstB(const OvShaderConstInfo& rConstInfo,OvBool bCheck)
{
	OvDevice kpDevice =  OvRenderer::GetInstance()->GetDevice();
	if (kpDevice)
	{
		HRESULT kHs = E_FAIL;
		kHs = kpDevice->SetVertexShaderConstantB(rConstInfo.RegistIndex,(const BOOL *)&bCheck,rConstInfo.ConstCount);
		return SUCCEEDED(kHs);
	}
	return false;
}
OvBool	OvShaderManager::GetVSConstB(const OvShaderConstInfo& rConstInfo,OvBool& bCheck)
{
	OvDevice kpDevice =  OvRenderer::GetInstance()->GetDevice();
	if (kpDevice)
	{
		HRESULT kHs = E_FAIL;
		kHs = kpDevice->GetVertexShaderConstantB(rConstInfo.RegistIndex,(BOOL *)&bCheck,rConstInfo.ConstCount);
		return SUCCEEDED(kHs);
	}
	return false;
}

OvBool	OvShaderManager::_SetVSConstF(const OvShaderConstInfo& rConstInfo,float* pConst,size_t stConstSize)
{
	OvDevice kpDevice =  OvRenderer::GetInstance()->GetDevice();
	if (kpDevice)
	{
		HRESULT kHs = E_FAIL;
		kHs = kpDevice->SetVertexShaderConstantF(rConstInfo.RegistIndex,(float*)pConst,rConstInfo.ConstCount);

		//! byte값은 값의 최소단위의 의미에서 곱해주며 현재로선 1값이니 의미없기도 하다.
		/*UINT uiRegConstSize = kConstInfo.ConstCount * sizeof(float) * 4 * sizeof(byte);
		if (stConstSize <= uiRegConstSize)
		{
		}
		else
		{
			OvFormatString kErrMsg("규약된 상수값 보다 큽니다.\n규약된 크기: %d byte\n요청된 크기: %d byte",uiRegConstSize,stConstSize);
			OvAssertMsg(kErrMsg);
		}*/
		return SUCCEEDED(kHs);
	}
	return false;
}
OvBool	OvShaderManager::_GetVSConstF(const OvShaderConstInfo& rConstInfo,float* pConst,size_t stConstSize)
{
	OvDevice kpDevice =  OvRenderer::GetInstance()->GetDevice();
	if (kpDevice)
	{
		HRESULT kHs = E_FAIL;
		if ( stConstSize < sizeof( float ) * 4 )
		{
			float temp[4];
			kHs = kpDevice->GetVertexShaderConstantF(rConstInfo.RegistIndex,(float*)temp,rConstInfo.ConstCount);
			memcpy( pConst, temp, stConstSize);
		}
		else
		{
			kHs = kpDevice->GetVertexShaderConstantF(rConstInfo.RegistIndex,(float*)pConst,rConstInfo.ConstCount);
		}

		//! byte값은 값의 최소단위의 의미에서 곱해주며 현재로선 1값이니 의미없기도 하다.
		/*UINT uiRegConstSize = kConstInfo.ConstCount * sizeof(float) * 4 * sizeof(byte);
		if (stConstSize >= uiRegConstSize)
		{
		}
		else
		{
			OvFormatString kErrMsg("규약된 상수값 보다 작습니다.\n규약된 크기: %d byte\n요청된 크기: %d byte",uiRegConstSize,stConstSize);
			OvAssertMsg(kErrMsg);
		}*/
		return SUCCEEDED(kHs);
	}
	return false;
}
OvBool	OvShaderManager::SetVSConst(const OvShaderConstInfo& rConstInfo,const OvMatrix& rType)
{
	OvMatrix kMat;
	kMat = OvMatrixTranspose(rType);
	return _SetVSConstF(rConstInfo,(float*)&(kMat),sizeof(OvMatrix));
}
OvBool	OvShaderManager::GetVSConst(const OvShaderConstInfo& rConstInfo,OvMatrix& rType)
{
	OvMatrix kMat;
	if (_GetVSConstF(rConstInfo,(float*)&(kMat),sizeof(OvMatrix)))
	{
		rType = OvMatrixTranspose(kMat);
		return true;
	}
	return false;
}
//////////////////////////////////////

OvBool	OvShaderManager::_SetPSConstF(const OvShaderConstInfo& rConstInfo,float* pConst,size_t stConstSize)
{
	OvDevice kpDevice =  OvRenderer::GetInstance()->GetDevice();
	if (kpDevice)
	{
		HRESULT kHs = E_FAIL;
		kHs = kpDevice->SetPixelShaderConstantF(rConstInfo.RegistIndex,(float*)pConst,rConstInfo.ConstCount);
		return SUCCEEDED(kHs);
	}
	return false;

}
OvBool	OvShaderManager::_GetPSConstF(const OvShaderConstInfo& rConstInfo,float* pConst,size_t stConstSize)
{
	OvDevice kpDevice =  OvRenderer::GetInstance()->GetDevice();
	if (kpDevice)
	{
		HRESULT kHs = E_FAIL;
		kHs = kpDevice->SetPixelShaderConstantF(rConstInfo.RegistIndex,(float*)pConst,rConstInfo.ConstCount);
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
OvShaderConstInfo::OvShaderConstInfo(const OvString& T, const OvString& N, UINT R,UINT C)
:ArrayCount(1)
,Type(T)
,Name(N)
,RegistIndex(R)
,ConstCount(C)
{};
OvShaderConstInfo::OvShaderConstInfo(UINT A, const OvString& T, const OvString& N, UINT R,UINT C)
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
			"규약된 쉐이더 상수 배열 크기를 벗어났습니다.\n"
			"접근 허용 인덱스: 0~%d \n"
			"접근 요청된 인덱스: %d ",ArrayCount-1,uiIndex);
		OvAssertMsg(kErrMsg);
		kuiAccess = ArrayCount;
	}
	return OvShaderConstInfo(Type,Name,RegistIndex+(ConstCount*uiIndex),ConstCount);
}