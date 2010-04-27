#pragma once

#include "OvRefBase.h"
#include "OvAutoPtr.h"
#include "OvUtility.h"

OvREF_POINTER(OvTexture)

class OvTexture : public OvRefBase
{
	OvRTTI_DECL(OvTexture);
public:
	OvTexture(void* pTexture);
	~OvTexture();
	void*	GetTexture();

private:
	struct OvPimple;
	OvAutoPtr<OvPimple> m_pPimple;

};