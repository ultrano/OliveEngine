#pragma once
#include "OvMemObject.h"
#include "OvUtility.h"
#include "OvAutoPtr.h"
#include "OvRefBase.h"
#include "OvObject.h"
#include "OvSingleton.h"

class OvObjectManager : public OvMemObject
{
	OvSingletonEx_DECL(OvObjectManager);
	friend OvREF_POINTER(OvObject);

public:

	OvObject*			FindObject(const OvObjectID& rObjHandle);

protected:

	OvObjectID			AllocObjectID(OvObject* _pObject);
	void				RecallObjectID(OvObject* _pObject);

private:


	//! Member Values (Ensconsed for encapsulation)
	//! Application can access member only using get,set interface
	struct OvPimple;
	OvAutoPtr<OvPimple> m_pPimple;
};