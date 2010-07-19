#pragma once
#include "OvRefBase.h"
#include <vector>

OvREF_POINTER(OvObject);
class OvObjectID;

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
	OvObjectSPtr	GetByID(OvObjectID& dhHandle);

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