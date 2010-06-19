#pragma once
#include "OvSmartPointer.h"
#include "OvObject.h"
#include "OvObjectID.h"
#include <vector>

OvREF_POINTER(OvObject);

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

	typedef vector<OvObjectSPtr>		tdObjectArray;
	tdObjectArray			m_tdObjArray;

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
		if ( OvRTTI_Util::IsKindOf< Type_0 >( pObject ) )
		{
			AddObject(pObject);
		}
	}
	return Count();
}