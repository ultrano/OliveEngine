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

	friend bool operator==(const OvObjectID& idRef0, const OvObjectID& idRef1);
	friend bool operator==( OvObjectID& idRef0,  OvObjectID& idRef1);

	friend bool operator!=(const OvObjectID& idRef0, const OvObjectID& idRef1);
	friend bool operator!=( OvObjectID& idRef0,  OvObjectID& idRef1);

	bool operator==(const OvObjectID& idRef);
	bool operator==(OvObjectID& idRef);

	bool operator!=(const OvObjectID& idRef);
	bool operator!=(OvObjectID& idRef);

	friend bool operator<(const OvObjectID& idRef0, const OvObjectID& idRef1);
	bool operator<(const OvObjectID& idRef);
	bool operator<(OvObjectID& idRef);

	friend bool operator>(const OvObjectID& idRef0, const OvObjectID& idRef1);
	bool operator>(const OvObjectID& idRef);
	bool operator>(OvObjectID& idRef);

private:

	friend class OvObjectManager;
	id_core_type core;
};