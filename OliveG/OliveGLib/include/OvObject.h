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
	const OvObjectID		GetObjectID();

protected:

	void	CallByFactory(OvStorage& rStorage);

private:

	string			m_strObjectName;
	OvObjectID		m_idObjectID;

};

#define OvFACTORY_MEMBER(__class_name) friend class OvObjectFactory;\
__class_name(OvStorage& rStorage){CallByFactory(rStorage);};\
static OvObjectSPtr	FactoryCallback(OvStorage& rStorage){return (new __class_name(rStorage));};