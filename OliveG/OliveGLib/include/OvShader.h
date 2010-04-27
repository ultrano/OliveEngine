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
	//! 이 두 함수는 파생될 버텍스,픽셀 쉐이더에서 공통으로 제공되야할
	//! 인터페이스이지만 부모인 OvShader에 의해서 접근되어선 안된다(잘못 사용되는것을 막기 위함)
	virtual bool Activate() = 0;
	virtual bool Inactivate() = 0;
private:

	struct OvPimple;
	OvAutoPtr<OvPimple> m_pPimple;
};

//OvShaderSPtr	OvLoadShader(const char* pFile,OvShader::eShaderType eType,const char* pEntranceFuncName,const char* pComplieVersion);
