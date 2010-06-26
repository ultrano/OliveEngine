#pragma once
#include "OvUtility.h"
#include "OvMemObject.h"
#include "OvShaderManager.h"
#include "OvAutoPtr.h"

#include "OvSingleton.h"

#define CONST_DECLARE_IN_APPLICATION
#include "OvMaterialConst.ops"
#include "OvMaterialConst.ovs"
#undef CONST_DECLARE_IN_APPLICATION

struct OvShaderConstInfo;
class OvMatrix;

class OvMaterialManager : public OvSingletonBase< OvMaterialManager >
{
public:
	OvMaterialManager();
	~OvMaterialManager();
private:

	struct OvPimple;
	OvAutoPtr<OvPimple> m_pPimple;

};