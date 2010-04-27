#pragma once
#include "OvUtility.h"
#include "OvRefBase.h"
#include "OvAutoPtr.h"
#include "OvObjectFactory.h"
#include "OvPropertyBag.h"

typedef DWORD OvObjectID;

OvREF_POINTER(OvObject);
class OvObject : public OvRefBase
{
	OvRTTI_DECL(OvObject);
	OvPROP_BAG_DECL(OvObject);

public:

	OvObject();
	~OvObject();

	//! Object Name
	void		SetName(const char* _pName);
	const char* GetName();

	//! ID of Object
	const OvObjectID		GetObjectID();

private:

	//! Member Values (Ensconsed for encapsulation)
	//! Application can access member only using get,set interface
	struct OvPimple;
	OvAutoPtr<OvPimple> m_pPimple;
	class OvProp_Pimple;
};