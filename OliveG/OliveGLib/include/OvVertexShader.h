#pragma once
#include "OvShader.h"

OvREF_POINTER(OvVertexShader);
class OvVertexShader : public OvShader
{
	OvRTTI_DECL(OvVertexShader);
public:

	OvVertexShader();
	~OvVertexShader();
public:

	void	SetVertexShaderInstance(void* pShaderInst);
	void*	GetVertexShaderInstance();

public:
	virtual bool Activate();
	virtual bool Inactivate();
private:

	struct OvPimple;
	OvAutoPtr<OvPimple> m_pPimple;
};

OvVertexShaderSPtr	OvLoadVertexShader(const char* pFile,const char* pEntranceFuncName,const char* pComplieVersion);
