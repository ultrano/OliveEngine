#pragma once
#pragma warning( disable : 4521 )
#include "OvTypeDef.h"
#include "OvMemObject.h"
//typedef OvUInt OvObjectID;;

class OvObjectID : public OvMemObject
{
public:

	typedef OvUInt id_core_type;

	static OvObjectID	INVALID;

	OvObjectID();
	OvObjectID( OvObjectID& );
	OvObjectID( id_core_type );
	OvObjectID( const OvObjectID& );
	~OvObjectID();

	friend OvBool operator==(const OvObjectID& idRef0, const OvObjectID& idRef1);
	friend OvBool operator==( OvObjectID& idRef0,  OvObjectID& idRef1);

	friend OvBool operator!=(const OvObjectID& idRef0, const OvObjectID& idRef1);
	friend OvBool operator!=( OvObjectID& idRef0,  OvObjectID& idRef1);

// 	OvBool operator==(const OvObjectID& idRef);
// 	OvBool operator==(OvObjectID& idRef);

// 	OvBool operator!=(const OvObjectID& idRef);
// 	OvBool operator!=(OvObjectID& idRef);

	friend OvBool operator<(const OvObjectID& idRef0, const OvObjectID& idRef1);
	OvBool operator<(const OvObjectID& idRef);
	OvBool operator<(OvObjectID& idRef);

	friend OvBool operator>(const OvObjectID& idRef0, const OvObjectID& idRef1);
	OvBool operator>(const OvObjectID& idRef);
	OvBool operator>(OvObjectID& idRef);

private:

	friend class OvObjectManager;
	id_core_type core;
};