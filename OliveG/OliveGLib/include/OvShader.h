#pragma once
#include "OvRefBase.h"
#include "OvAutoPtr.h"
#include "OvShaderConstantTable.h"

OvREF_POINTER(OvShader);
class	OvShader : public OvRefBase
{
	OvRTTI_DECL(OvShader);

public:

	OvShader();
	~OvShader();

	void	SetConstantTable(OvShaderConstantTableSPtr pConstTable);
	OvShaderConstantTableSPtr GetConstantTable();

private:
	//! �� �� �Լ��� �Ļ��� ���ؽ�,�ȼ� ���̴����� �������� �����Ǿ���
	//! �������̽������� �θ��� OvShader�� ���ؼ� ���ٵǾ �ȵȴ�(�߸� ���Ǵ°��� ���� ����)
	virtual bool Activate() = 0;
	virtual bool Inactivate() = 0;
private:

	struct OvPimple;
	OvAutoPtr<OvPimple> m_pPimple;
};

//OvShaderSPtr	OvLoadShader(const char* pFile,OvShader::eShaderType eType,const char* pEntranceFuncName,const char* pComplieVersion);
