#pragma once
#include "OvUtility.h"
#include "OvRefBase.h"
#include "OvAutoPtr.h"
#include "OvPropertyBag.h"
#include "OvObjectFactory.h"
#include "OvObjectID.h"
#include "OvObjectOutputStream.h"
#include "OvObjectInputStream.h"

class OvStorage;
class OvObjectProperties;

OvREF_POINTER(OvObject);
typedef OvSet<OvObjectSPtr> OvObjectSet;

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

	//! Stream
	virtual void Serialize( OvObjectOutputStream & output );
	virtual void Deserialize( OvObjectInputStream & input );

	//! ID of Object
	OvObjectID		GetObjectID();

private:

	OvObjectID		m_idObjectID;

};

void ExtractProperties( OvObject* obj, OvObjectProperties& prop );
void InjectProperties( OvObject* obj, OvObjectProperties& prop );