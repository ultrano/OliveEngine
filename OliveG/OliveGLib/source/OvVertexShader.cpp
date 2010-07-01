#include "OvVertexShader.h"
#include "OvRenderer.h"
#include "d3dx9.h"
OvRTTI_IMPL(OvVertexShader,OvShader);

struct OvVertexShader::OvPimple : OvMemObject
{
	LPDIRECT3DVERTEXSHADER9	m_pShaderInst;
};

OvVertexShader::OvVertexShader()
:m_pPimple(OvNew OvVertexShader::OvPimple)
{

}
OvVertexShader::~OvVertexShader()
{
	if (m_pPimple->m_pShaderInst)
	{
		m_pPimple->m_pShaderInst->Release();
	}
}
void	OvVertexShader::SetVertexShaderInstance(void* pShaderInst)
{
	m_pPimple->m_pShaderInst = (LPDIRECT3DVERTEXSHADER9)pShaderInst;
}
void*	OvVertexShader::GetVertexShaderInstance()
{
	return m_pPimple->m_pShaderInst;
}

bool OvVertexShader::Activate()
{
	LPDIRECT3DDEVICE9 kpDevice =  OvRenderer::GetInstance()->GetDevice();
	LPDIRECT3DVERTEXSHADER9 kpShaderInst = (LPDIRECT3DVERTEXSHADER9)GetVertexShaderInstance();
	if (kpDevice && kpShaderInst)
	{
		return SUCCEEDED(kpDevice->SetVertexShader(kpShaderInst));
	}
	return false;
}
bool OvVertexShader::Inactivate()
{
	LPDIRECT3DDEVICE9 kpDevice =  OvRenderer::GetInstance()->GetDevice();
	if (kpDevice)
	{
		kpDevice->SetVertexShader(NULL);
		return true;
	}
	return false;
}

OvVertexShaderSPtr	OvLoadVertexShader(const char* pFile,const char* pEntranceFuncName,const char* pComplieVersion)
{

	LPDIRECT3DDEVICE9 kpDevice =  OvRenderer::GetInstance()->GetDevice();
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

			khs = kpDevice->CreateVertexShader((DWORD*)kShaderBuffer->GetBufferPointer(),(LPDIRECT3DVERTEXSHADER9*)&kpShaderInstance );

			kShaderBuffer->Release();
			if (SUCCEEDED(khs))
			{
				OvShaderConstantTableSPtr kpConstTable = OvNew OvShaderConstantTable((void*)kpConstTableInst);
				OvVertexShaderSPtr kpShader = OvNew OvVertexShader();
				kpShader->SetVertexShaderInstance((void*)kpShaderInstance);
				kpShader->SetConstantTable(kpConstTable);
				return kpShader;
			}
		}
	}

	return NULL;
}