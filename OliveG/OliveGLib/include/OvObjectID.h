#pragma once

//typedef unsigned int OvObjectID;;

class OvObjectID
{
public:

	typedef unsigned int id_core_type;

	static OvObjectID	INVALID;

	OvObjectID();
	OvObjectID( OvObjectID& );
	OvObjectID( id_core_type );
	OvObjectID( const OvObjectID& );

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