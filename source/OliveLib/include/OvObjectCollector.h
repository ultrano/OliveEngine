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

	OvObjectSPtr	GetByAt(OvInt iIndex);
	OvObjectSPtr	GetByName( const OvString& name );
	OvObjectSPtr	GetByID( const OvObjectID& objectID );

	DWORD			Count();
	void			Clear();

	OvBool			AddObject(OvObjectSPtr pObj);
	OvBool			AddObject(OvObjectCollector& pObjContainer);
	OvObjectSPtr	RemoveObject(OvObjectSPtr pObj);
	OvObjectSPtr	RemoveObject( const OvObjectID& objectID );

	OvBool			IsCollected(OvObjectSPtr pObj);

private:

	typedef vector<OvObjectSPtr>		tdObjectArray;
	tdObjectArray			m_tdObjArray;

};