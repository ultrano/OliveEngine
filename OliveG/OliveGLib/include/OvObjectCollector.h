#pragma once
#include "OvObject.h"
#include "OvAutoPtr.h"

OvREF_POINTER(OvObject)

class OvObjectCollector : public OvMemObject
{

public:

	OvObjectCollector();
	OvObjectCollector(OvObjectCollector&);
	OvObjectCollector(const OvObjectCollector&);
	~OvObjectCollector();


	template<typename Type_0>
	DWORD			CollectTreeObject(OvObjectSPtr	pObject);

	OvObjectSPtr	GetByAt(int iIndex);
	OvObjectSPtr	GetByName(const char* pName);
	OvObjectSPtr	GetByHandle(OvObjectID& dhHandle);

	DWORD			Count();
	void			Clear();

	bool			AddObject(OvObjectSPtr pObj);
	bool			AddObject(OvObjectCollector& pObjContainer);
	OvObjectSPtr	RemoveObject(OvObjectSPtr pObj);

	bool			IsCollected(OvObjectSPtr pObj);

private:

	//! Member Values (Ensconsed for encapsulation)
	//! Application can access member only using get,set interface
	struct OvPimple;
	OvAutoPtr<OvPimple> m_pPimple;
};
template<typename Type_0>
DWORD OvObjectCollector::CollectTreeObject(OvObjectSPtr	pObject)
{
	OvObjectCollector	kContainer;
	if (pObject->IsNode())
	{
		OvXNodeSPtr	kpConvertToNode = pObject;
		for (int i=0;i<kpConvertToNode->GetChildCount();++i)
		{
			CollectTreeObject<Type_0>(kpConvertToNode->GetChildeAt(i));
		}
	}
	else
	{
		if (OvRTTI_IsKindOf(Type_0,pObject))
		{
			AddObject(pObject);
		}
	}
	return Count();
}