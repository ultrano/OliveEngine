#pragma once
#include "OvRefBase.h"
#include "OvAutoPtr.h"
OvREF_POINTER(OvXNode);

OvREF_POINTER(OvMassBuilder);

class OvMassBuilder : public OvRefBase
{
public:
	OvXNodeSPtr	Build(const char* pFile);
private:
	struct OvPimple;
	OvAutoPtr<OvPimple> m_pPimple;
};