#pragma once
#include "OvUtility.h"
#include "OvRefBase.h"
#include "OvAutoPtr.h"
#include "OvPropertyBag.h"

#include "OvObjectID.h"

class OvStorage;
OvREF_POINTER(OvObject);
class OvObject : public OvRefBase
{
	OvRTTI_DECL(OvObject);
	OvPROP_BAG_DECL(OvObject);

public:

	OvObject();
	OvObject(OvStorage& rStorage);
	~OvObject(); 

	//! Object Name
	void		SetName(const char* _pName);
	const char* GetName();

	//! ID of Object
	OvObjectID		GetObjectID();

private:

	string			m_strObjectName;
	OvObjectID		m_idObjectID;

};

#define OvFACTORY_MEMBER(__class_name) friend class OvObjectFactory;\
__class_name(OvObjectID& objID){objID = GetObjectID();};\
static OvObjectSPtr	FactoryCallback(OvObjectID& objID){return (new __class_name(objID));};