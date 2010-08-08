#pragma once
#include "OvRefBase.h"
#include "OvAutoPtr.h"

class OvMatrix;

OvREF_POINTER(OvShaderConstantTable)
class OvShaderConstantTable : public OvRefBase
{
public:
	OvRTTI_DECL(OvShaderConstantTable);

	OvShaderConstantTable(void* pConstTableInstance);
	~OvShaderConstantTable();

	bool	SetUserConstantF(const char* pConstName,float* pConst,size_t stByteSize);

	bool	SetMatrix(const char* pConstName,const OvMatrix&);

	void*	GetConstTableInst();

private:

	struct OvPimple;
	OvAutoPtr<OvPimple> m_pPimple;

};
