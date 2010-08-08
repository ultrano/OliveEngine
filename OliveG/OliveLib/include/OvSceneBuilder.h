#pragma once
#include "OvRefBase.h"
#include "OvAutoPtr.h"
OvREF_POINTER(OvXNode);

OvREF_POINTER(OvSceneBuilder);
class OvSceneBuilder : public OvRefBase
{
public:
	OvSceneBuilder();
	~OvSceneBuilder();
	OvXNodeSPtr BuildScene(const char* pFile);
	void BuildMeshObject(const char* pFile);
	void BuildMesh(const char* pFile);
private:
	struct OvPimple;
	OvAutoPtr< OvPimple> m_pPimple;
};