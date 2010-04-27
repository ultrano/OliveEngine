#pragma once
#include "OvRefBase.h"
#include "OvAutoPtr.h"
#include "OvNodeBuilder.h"

OvREF_POINTER(OvXNode);

OvREF_POINTER(OvNodeTreeBuilder);

class OvNodeTreeBuilder : public OvRefBase
{
public:
	OvNodeTreeBuilder();
	~OvNodeTreeBuilder();
	void		AddElementObject(SNodeInheritInfo& rNodeInfo);
	void		AddElementObject(int iHandle,int iParentHandle,OvXObjectSPtr pObject);
	OvXNodeSPtr	Build();
private:
	struct OvPimple;
	OvAutoPtr<OvPimple> m_pPimple;
};