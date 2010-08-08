#pragma once
#include "OvStoreObject.h"

class OvStoreNode : public OvStoreObject
{
	OvRTTI_DECL(OvStoreNode);
public:

	OvStoreNode();
	~OvStoreNode();

	unsigned int	ChildCount();
	void			InsertObject(OvStoreObject* pObject);
	OvStoreObject*	FindChild(const char* pName);
	OvStoreObject*	FindDataChild(const char* pName);
	OvStoreObject*	FindNodeChild(const char* pName);
	OvStoreObject*	ChildAt(unsigned int iIndex);

	virtual OvStoreObject*	MakeCopyInstance();
	virtual bool			CopyTo(OvStoreObject*);

private:

	//! Member Values (Ensconsed for encapsulation)
	//! Application can access member only using get,set interface
	struct OvPimple;
	OvAutoPtr<OvPimple> m_pPimple;

};