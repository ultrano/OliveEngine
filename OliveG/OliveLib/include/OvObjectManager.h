#pragma once
#include "OvMemObject.h"
#include "OvUtility.h"
#include "OvAutoPtr.h"
#include "OvRefBase.h"
#include "OvObject.h"
#include "OvSingleton.h"
#include <list>
#include <time.h>

class OvObjectManager : public OvSingletonBase< OvObjectManager >
{
	friend OvREF_POINTER(OvObject);

	typedef map<OvObjectID,OvObject*>			object_table;

public:

	OvObjectManager();
	~OvObjectManager();

	OvObject*			FindObject(const OvObjectID& rObjHandle);

protected:

	OvObjectID			AllocObjectID(OvObject* _pObject);
	void				RecallObjectID(OvObject* _pObject);

private:


	//! Member Values (Ensconsed for encapsulation)
	//! Application can access member only using get,set interface
	struct OvPimple;
	OvAutoPtr<OvPimple> m_pPimple;

	object_table	m_objectTable;
};