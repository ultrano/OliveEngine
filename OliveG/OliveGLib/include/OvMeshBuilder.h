#pragma once
#include "OvRefBase.h"
#include "OvAutoPtr.h"
OvREF_POINTER(OvMesh);

OvREF_POINTER(OvMeshBuilder);
class OvMeshBuilder : public OvRefBase
{
public:
	OvMeshSPtr	Build(const char* pFile);
private:
	struct OvPimple;
	OvAutoPtr<OvPimple> m_pPimple;
};