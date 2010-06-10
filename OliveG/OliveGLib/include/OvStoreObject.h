

#pragma once

#include "OvMemObject.h"
#include "OvRTTI.h"
#include "OvAutoPtr.h"

class TiXmlElement;

class OvStoreObject : public OvMemObject
{
	OvRTTI_DECL_ROOT(OvStoreObject);

public:

	OvStoreObject();
	virtual ~OvStoreObject();

	void		SetName(const char* pName);
	const char* GetName();

	virtual OvStoreObject*	MakeCopyInstance() = 0;
	virtual bool			CopyTo(OvStoreObject*) = 0;

private:

	//! Member Values (Ensconsed for encapsulation)
	//! Application can access member only using get,set interface
	struct OvPimple;
	OvAutoPtr<OvPimple> m_pPimple;

};
