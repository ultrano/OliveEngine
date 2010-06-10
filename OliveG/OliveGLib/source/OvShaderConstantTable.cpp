#include "OvShaderConstantTable.h"
#include "OvRenderer.h"
#include "d3dx9.h"
OvRTTI_IMPL(OvShaderConstantTable);
struct OvShaderConstantTable::OvPimple : OvMemObject
{
	LPD3DXCONSTANTTABLE	m_pConstTable;
};
OvShaderConstantTable::OvShaderConstantTable(void* pConstTableInstance)
:m_pPimple(OvNew OvShaderConstantTable::OvPimple)
{
	m_pPimple->m_pConstTable = (LPD3DXCONSTANTTABLE)pConstTableInstance;
}
OvShaderConstantTable::~OvShaderConstantTable()
{
	if (m_pPimple->m_pConstTable)
	{
		m_pPimple->m_pConstTable->Release();
	}
}


bool	OvShaderConstantTable::SetUserConstantF(const char* pConstName,float* pConst,size_t stByteSize)
{
	LPD3DXCONSTANTTABLE	kpConstTable = (LPD3DXCONSTANTTABLE)GetConstTableInst();
	LPDIRECT3DDEVICE9 kpDevice =  (LPDIRECT3DDEVICE9)OvRenderer::GetInstance()->GetDevice();
	if (kpConstTable && pConstName && kpDevice)
	{
		HRESULT khs;
		D3DXHANDLE khConstHandle = kpConstTable->GetConstantByName(0,pConstName);
		khs = kpConstTable->SetValue(kpDevice,khConstHandle,pConst,stByteSize);
		return (SUCCEEDED(khs));
	}
	return false;

}
bool	OvShaderConstantTable::SetMatrix(const char* pConstName,const OvMatrix& rMat)
{
	LPD3DXCONSTANTTABLE	kpConstTable = (LPD3DXCONSTANTTABLE)GetConstTableInst();
	LPDIRECT3DDEVICE9 kpDevice =  (LPDIRECT3DDEVICE9)OvRenderer::GetInstance()->GetDevice();
	if (kpConstTable && pConstName && kpDevice)
	{
		HRESULT khs;
		D3DXHANDLE khConstHandle = kpConstTable->GetConstantByName(0,pConstName);
		khs = kpConstTable->SetMatrix(kpDevice,khConstHandle,(D3DXMATRIX*)&rMat);
		return (SUCCEEDED(khs));
	}

}
void*	OvShaderConstantTable::GetConstTableInst()
{
	return m_pPimple->m_pConstTable;
}