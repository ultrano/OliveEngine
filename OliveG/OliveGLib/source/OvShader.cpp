#include "OvShader.h"
#include "OvRenderer.h"
#include "OvShaderConstantTable.h"
#include "d3dx9.h"
OvRTTI_IMPL(OvShader);

struct OvShader::OvPimple : OvMemObject
{
	OvShaderConstantTableSPtr	m_pConstTable;
};

OvShader::OvShader()
:m_pPimple(OvNew OvShader::OvPimple)
{
}
OvShader::~OvShader()
{
}
void	OvShader::SetConstantTable(OvShaderConstantTableSPtr pConstTable)
{
	m_pPimple->m_pConstTable = pConstTable;
}
OvShaderConstantTableSPtr OvShader::GetConstantTable()
{
	return m_pPimple->m_pConstTable;
}
/*
OvShaderSPtr	OvLoadShader(const char* pFile,OvShader::eShaderType eType,const char* pEntranceFuncName,const char* pComplieVersion)
{
	LPDIRECT3DDEVICE9 kpDevice =  (LPDIRECT3DDEVICE9)OvRenderer::GetInstance()->GetDevice();
	IUnknown*	kpShaderInstance = NULL;
	LPD3DXCONSTANTTABLE	kpConstTable = NULL;
	LPD3DXBUFFER kShaderBuffer = NULL;
	LPD3DXBUFFER kShaderErrorMsg = NULL;
	
	if (FAILED(D3DXCompileShaderFromFile(pFile,NULL,NULL,pEntranceFuncName,pComplieVersion,D3DXSHADER_DEBUG,&kShaderBuffer,&kShaderErrorMsg,&kpConstTable)))
	{
		if (kShaderErrorMsg)
		{
			OvAssertMsg((char*)(kShaderErrorMsg->GetBufferPointer()));
		}
		return NULL;
	}
	if (kShaderErrorMsg)
	{
		kShaderErrorMsg->Release();
	}
	if (kShaderBuffer)
	{
		HRESULT khs;
		switch (eType)
		{
		case OvShader::eShaderType_Vertex : 
			khs = kpDevice->CreateVertexShader((DWORD*)kShaderBuffer->GetBufferPointer(),(LPDIRECT3DVERTEXSHADER9*)&kpShaderInstance );
			break;
		case OvShader::eShaderType_Pixel : 
			khs = kpDevice->CreatePixelShader((DWORD*)kShaderBuffer->GetBufferPointer(),(LPDIRECT3DPIXELSHADER9*)&kpShaderInstance);
			break;
		}
		kShaderBuffer->Release();
		if (SUCCEEDED(khs))
		{
			OvShaderSPtr kpShader = new OvShader((void*)kpShaderInstance,eType,(void*)kpConstTable);
			return kpShader;
		}
	}
	return NULL;
}
*/