#pragma once
#include "OvShader.h"

OvREF_POINTER(OvPixelShader);
class OvPixelShader : public OvShader
{
	OvRTTI_DECL(OvPixelShader);
public:

	OvPixelShader();
	~OvPixelShader();
public:

	void	SetPixelShaderInstance(void* pShaderInst);
	void*	GetPixelShaderInstance();

public:
	virtual bool Activate();
	virtual bool Inactivate();
private:

	struct OvPimple;
	OvAutoPtr<OvPimple> m_pPimple;
};
OvPixelShaderSPtr	OvLoadPixelShader(const char* pFile,const char* pEntranceFuncName,const char* pComplieVersion);