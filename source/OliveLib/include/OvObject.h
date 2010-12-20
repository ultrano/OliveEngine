#pragma once
#include "OvUtility.h"
#include "OvRefBase.h"
#include "OvAutoPtr.h"
#include "OvPropertyBag.h"
#include "OvObjectFactory.h"
#include <map>

#include "OvObjectID.h"

class OvStorage;
class OvObjectProperties;
OvREF_POINTER(OvObject);
class OvObject : public OvRefBase
{
	OvRTTI_DECL(OvObject);
private:

	OvObject( OvObject& );
	OvObject( const OvObject& );

public:

	OvObject();
	virtual ~OvObject(); 

	//! Clone Object
	OvObjectSPtr		 Clone();
	virtual OvObjectSPtr CustomClone();

	//! ID of Object
	OvObjectID		GetObjectID();

private:

	OvObjectID		m_idObjectID;

};

void ExtractProperties( OvObject* obj, OvObjectProperties& prop );
void InjectProperties( OvObject* obj, OvObjectProperties& prop );