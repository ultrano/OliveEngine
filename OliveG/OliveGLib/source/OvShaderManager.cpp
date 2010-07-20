#include "OvShaderManager.h"
#include "OvShaderConstantTable.h"
#include "OvRenderer.h"
#include "OvTransform.h"
#include "OvStringUtility.h"
#include "OvTexture.h"
#include <d3dx9.h>
#include <map>

/////////////////////////// 테스트 유틸리티  ///////////////////////////////////
//////////////////////////////////////////////////////////////////////////
struct SDxAutoRelease
{
	SDxAutoRelease( IUnknown* target ):m_target( target ){};
	~SDxAutoRelease(){if(m_target)m_target->Release();};

	IUnknown* m_target;
};
//////////////////////////////////////////////////////////////////////////
//////////////////////////////////////////////////////////////////////////

LPD3DXBUFFER	CompileShaderFromFile( const string& file, const string& funcName, const string& version, LPD3DXINCLUDE includer = NULL)
{
	LPD3DXBUFFER	shaderBuffer = NULL;
	LPD3DXBUFFER	compileResult = NULL;
	HRESULT hr = D3DXCompileShaderFromFile
		( file.c_str()
		, NULL
		, includer
		, funcName.c_str()
		, version.c_str()
		, D3DXSHADER_DEBUG
		, &shaderBuffer
		, &compileResult
		, NULL);
	if ( SUCCEEDED( hr ) )
	{
		return shaderBuffer;
	}
	else
	{
		SDxAutoRelease autoRelease0( compileResult );
		SDxAutoRelease autoRelease1( shaderBuffer );
		if ( compileResult )
		{
			OvAssertMsg( ( char* )compileResult->GetBufferPointer() );
			compileResult->Release();
		}
		if ( shaderBuffer )
		{
			shaderBuffer->Release();
		}
		return NULL;
	}
	return NULL;
}
//////////////////////////////////////////////////////////////////////////
//////////////////////////////////////////////////////////////////////////

LPD3DXBUFFER	CompileShaderFromCode( const string& code, const string& funcName, const string& version, LPD3DXINCLUDE includer = NULL)
{
	LPD3DXBUFFER	shaderBuffer = NULL;
	LPD3DXBUFFER	compileResult = NULL;
	HRESULT hr = D3DXCompileShader
		( code.c_str()
		, code.size()
		, NULL
		, includer
		, funcName.c_str()
		, version.c_str()
		, D3DXSHADER_DEBUG
		, &shaderBuffer
		, &compileResult
		, NULL);
	if ( SUCCEEDED( hr ) )
	{
		return shaderBuffer;
	}
	else
	{
		SDxAutoRelease autoRelease0( compileResult );
		SDxAutoRelease autoRelease1( shaderBuffer );
		if ( compileResult )
		{
			OvAssertMsg( ( char* )compileResult->GetBufferPointer() );
			compileResult->Release();
		}
		if ( shaderBuffer )
		{
			shaderBuffer->Release();
		}
		return NULL;
	}
	return NULL;
}
//////////////////////////////////////////////////////////////////////////
//////////////////////////////////////////////////////////////////////////

OvShaderManager::OvShaderManager()
{
}
OvShaderManager::~OvShaderManager()
{

}

LPDIRECT3DVERTEXSHADER9	OvShaderManager::CreateVertexShaderFromFile( const string& file, const string& func, const string& version, LPD3DXINCLUDE includer)
{
	LPD3DXBUFFER shaderBuffer = CompileShaderFromFile( file, func, version, includer );
	SDxAutoRelease autoRelease( shaderBuffer );
	if ( shaderBuffer )
	{
		LPDIRECT3DDEVICE9 device = OvRenderer::GetInstance()->GetDevice();
		if ( device )
		{
			LPDIRECT3DVERTEXSHADER9 shader = NULL;
			device->CreateVertexShader( (DWORD*)shaderBuffer->GetBufferPointer(), &shader );
			return shader;
		}
	}
	return NULL;
}
LPDIRECT3DPIXELSHADER9	OvShaderManager::CreatePixelShaderFromFile( const string& file, const string& func, const string& version, LPD3DXINCLUDE includer)
{
	LPD3DXBUFFER shaderBuffer = CompileShaderFromFile( file, func, version, includer );
	SDxAutoRelease autoRelease( shaderBuffer );
	if ( shaderBuffer )
	{
		LPDIRECT3DDEVICE9 device = OvRenderer::GetInstance()->GetDevice();
		if ( device )
		{
			LPDIRECT3DPIXELSHADER9 shader = NULL;
			device->CreatePixelShader( (DWORD*)shaderBuffer->GetBufferPointer(), &shader );
			return shader;
		}
	}
	return NULL;
}

LPDIRECT3DVERTEXSHADER9 OvShaderManager::CreateVertexShaderFromCode( const string& code, const string& func, const string& version, LPD3DXINCLUDE includer /*= NULL*/ )
{
	LPD3DXBUFFER shaderBuffer = CompileShaderFromCode( code, func, version, includer );
	SDxAutoRelease autoRelease( shaderBuffer );
	if ( shaderBuffer )
	{
		LPDIRECT3DDEVICE9 device = OvRenderer::GetInstance()->GetDevice();
		if ( device )
		{
			LPDIRECT3DVERTEXSHADER9 shader = NULL;
			device->CreateVertexShader( (DWORD*)shaderBuffer->GetBufferPointer(), &shader );
			return shader;
		}
	}
	return NULL;
}

LPDIRECT3DPIXELSHADER9 OvShaderManager::CreatePixelShaderFromCode( const string& code, const string& func, const string& version, LPD3DXINCLUDE includer /*= NULL*/ )
{
	LPD3DXBUFFER shaderBuffer = CompileShaderFromCode( code, func, version, includer );
	SDxAutoRelease autoRelease( shaderBuffer );
	if ( shaderBuffer )
	{
		LPDIRECT3DDEVICE9 device = OvRenderer::GetInstance()->GetDevice();
		if ( device )
		{
			LPDIRECT3DPIXELSHADER9 shader = NULL;
			device->CreatePixelShader( (DWORD*)shaderBuffer->GetBufferPointer(), &shader );
			return shader;
		}
	}
	return NULL;
}


bool	OvShaderManager::SetVSConstB(const OvShaderConstInfo& rConstInfo,bool bCheck)
{
	LPDIRECT3DDEVICE9 kpDevice =  OvRenderer::GetInstance()->GetDevice();
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
	LPDIRECT3DDEVICE9 kpDevice =  OvRenderer::GetInstance()->GetDevice();
	if (kpDevice)
	{
		HRESULT kHs = E_FAIL;
		kHs = kpDevice->GetVertexShaderConstantB(rConstInfo.RegistIndex,(BOOL *)&bCheck,rConstInfo.ConstCount);
		return SUCCEEDED(kHs);
	}
	return false;
}

bool	OvShaderManager::_SetVSConstF(const OvShaderConstInfo& rConstInfo,float* pConst,size_t stConstSize)
{
	LPDIRECT3DDEVICE9 kpDevice =  OvRenderer::GetInstance()->GetDevice();
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
bool	OvShaderManager::_GetVSConstF(const OvShaderConstInfo& rConstInfo,float* pConst,size_t stConstSize)
{
	LPDIRECT3DDEVICE9 kpDevice =  OvRenderer::GetInstance()->GetDevice();
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
bool	OvShaderManager::SetVSConst(const OvShaderConstInfo& rConstInfo,const OvMatrix& rType)
{
	OvMatrix kMat;
	kMat = OvMatrixTranspose(rType);
	return _SetVSConstF(rConstInfo,(float*)&(kMat),sizeof(OvMatrix));
}
bool	OvShaderManager::GetVSConst(const OvShaderConstInfo& rConstInfo,OvMatrix& rType)
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

bool	OvShaderManager::_SetPSConstF(const OvShaderConstInfo& rConstInfo,float* pConst,size_t stConstSize)
{
	LPDIRECT3DDEVICE9 kpDevice =  OvRenderer::GetInstance()->GetDevice();
	if (kpDevice)
	{
		HRESULT kHs = E_FAIL;
		kHs = kpDevice->SetPixelShaderConstantF(rConstInfo.RegistIndex,(float*)pConst,rConstInfo.ConstCount);
		return SUCCEEDED(kHs);
	}
	return false;

}
bool	OvShaderManager::_GetPSConstF(const OvShaderConstInfo& rConstInfo,float* pConst,size_t stConstSize)
{
	LPDIRECT3DDEVICE9 kpDevice =  OvRenderer::GetInstance()->GetDevice();
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
	LPDIRECT3DDEVICE9 kpDevice =  OvRenderer::GetInstance()->GetDevice();
	if (kpDevice && pTexture)
	{
		HRESULT kHs = E_FAIL;
		kHs = kpDevice->SetTexture( uiSamplerIndex, pTexture->ToDxTexture() );
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
			"규약된 쉐이더 상수 배열 크기를 벗어났습니다.\n"
			"접근 허용 인덱스: 0~%d \n"
			"접근 요청된 인덱스: %d ",ArrayCount-1,uiIndex);
		OvAssertMsg(kErrMsg);
		kuiAccess = ArrayCount;
	}
	return OvShaderConstInfo(Type,Name,RegistIndex+(ConstCount*uiIndex),ConstCount);
}