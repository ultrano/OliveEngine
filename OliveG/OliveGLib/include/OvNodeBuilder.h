#pragma once
#include "OvRefBase.h"
#include "OvAutoPtr.h"

OvREF_POINTER(OvNodeBuilder);
OvREF_POINTER(OvXObject);
OvREF_POINTER(OvXNode);


struct SNodeInheritInfo
{
	SNodeInheritInfo(int iHandle,int iParentHandle,OvXObjectSPtr mObject)
		:mHandle(iHandle)
		,mParentHandle(iParentHandle)
		,mObject(mObject)
	{

	};
	SNodeInheritInfo()
		:mHandle(-1)
		,mParentHandle(-1)
		,mObject(NULL)
	{
	};
	int mHandle;
	int mParentHandle;
	OvXObjectSPtr mObject;
};

class OvNodeBuilder : public OvRefBase
{
public:
	SNodeInheritInfo	BuildNodeInfo(const char* pFile);
	OvXNodeSPtr			Build(const char* pFile);
private:
	struct OvPimple;
	OvAutoPtr<OvPimple> m_pPimple;
};