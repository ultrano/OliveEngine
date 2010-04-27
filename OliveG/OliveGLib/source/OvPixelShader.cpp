#include "OvPixelShader.h"
#include "OvRenderer.h"
#include "d3dx9.h"
OvRTTI_IMPL(OvPixelShader,OvShader);

struct OvPixelShader::OvPimple : OvMemObject
{
	LPDIRECT3DPIXELSHADER9	m_pShaderInst;
};

OvPixelShader::OvPixelShader()
:m_pPimple(OvNew OvPixelShader::OvPimple)
{

}
OvPixelShader::~OvPixelShader()
{
	if (m_pPimple->m_pShaderInst)
	{
		m_pPimple->m_pShaderInst->Release();
	}
}
void	OvPixelShader::SetPixelShaderInstance(void* pShaderInst)
{
	m_pPimple->m_pShaderInst = (LPDIRECT3DPIXELSHADER9)pShaderInst;
}
void*	OvPixelShader::GetPixelShaderInstance()
{
	return m_pPimple->m_pShaderInst;
}

bool OvPixelShader::Activate()
{
	LPDIRECT3DDEVICE9 kpDevice =  (LPDIRECT3DDEVICE9)OvRenderer::GetInstance()->GetDevice();
	LPDIRECT3DPIXELSHADER9 kpShaderInst = (LPDIRECT3DPIXELSHADER9)GetPixelShaderInstance();
	if (kpDevice && kpShaderInst)
	{
		return SUCCEEDED(kpDevice->SetPixelShader(kpShaderInst));
	}
	return false;
}
bool OvPixelShader::Inactivate()
{
	LPDIRECT3DDEVICE9 kpDevice =  (LPDIRECT3DDEVICE9)OvRenderer::GetInstance()->GetDevice();
	if (kpDevice)
	{
		kpDevice->SetPixelShader(NULL);
		return true;
	}
	return false;
}


OvPixelShaderSPtr	OvLoadPixelShader(const char* pFile,const char* pEntranceFuncName,const char* pComplieVersion)
{

	LPDIRECT3DDEVICE9 kpDevice =  (LPDIRECT3DDEVICE9)OvRenderer::GetInstance()->GetDevice();
	IUnknown*	kpShaderInstance = NULL;
	LPD3DXCONSTANTTABLE	kpConstTableInst = NULL;
	LPD3DXBUFFER kShaderBuffer = NULL;
	LPD3DXBUFFER kCompileResultMsg = NULL;
	HRESULT kHs = E_FAIL;
	kHs = D3DXCompileShaderFromFile(pFile,NULL,NULL,pEntranceFuncName,pComplieVersion,D3DXSHADER_DEBUG,&kShaderBuffer,&kCompileResultMsg,&kpConstTableInst);

	if ( (kCompileResultMsg))
	{
		if (FAILED(kHs))
		{
			OvAssertMsg((char*)(kCompileResultMsg->GetBufferPointer()));
		}
		kCompileResultMsg->Release();
	}

	if (SUCCEEDED(kHs))
	{
		if (kShaderBuffer)
		{
			HRESULT khs;

			khs = kpDevice->CreatePixelShader((DWORD*)kShaderBuffer->GetBufferPointer(),(LPDIRECT3DPIXELSHADER9*)&kpShaderInstance );

			kShaderBuffer->Release();
			if (SUCCEEDED(khs))
			{
				OvShaderConstantTableSPtr kpConstTable = OvNew OvShaderConstantTable((void*)kpConstTableInst);
				OvPixelShaderSPtr kpShader = OvNew OvPixelShader();
				kpShader->SetPixelShaderInstance((void*)kpShaderInstance);
				kpShader->SetConstantTable(kpConstTable);
				return kpShader;
			}
		}
	}
	return NULL;
}