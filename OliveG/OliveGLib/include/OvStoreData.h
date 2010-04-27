#pragma once

#include "OvStoreObject.h"


class OvStoreData : public OvStoreObject
{
	OvRTTI_DECL(OvStoreData);
public:

	OvStoreData();
	OvStoreData(const char* pName);
	~OvStoreData();

	void		SetDataString(const char* pData);
	const char* GetDataString();

	void		SetDataType(const char* pType);
	const char* GetDataType();

	virtual OvStoreObject*	MakeCopyInstance();
	virtual bool			CopyTo(OvStoreObject*);

private:

	//! Member Values (Ensconsed for encapsulation)
	//! Application can access member only using get,set interface
	struct OvPimple;
	OvAutoPtr<OvPimple> m_pPimple;

};