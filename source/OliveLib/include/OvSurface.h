#pragma once

#include "OvRefBase.h"
#include "OvAutoPtr.h"

OvREF_POINTER(OvSurface)

class OvSurface : public OvRefBase
{
public:
	OvSurface(void* pSurface);
	~OvSurface();

	void*	GetSurface();

private:
	struct OvPimple;
	OvAutoPtr<OvPimple> m_pPimple;
};