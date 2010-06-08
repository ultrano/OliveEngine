#pragma once

//typedef unsigned int OvObjectID;;

class OvObjectID
{
	friend class OvObjectManager;
	OvObjectID( unsigned int );
	unsigned int core;
public:

	static OvObjectID	INVALID;

	OvObjectID();
	OvObjectID( OvObjectID& );
	OvObjectID( const OvObjectID& );

	friend bool operator==(const OvObjectID& idRef0, const OvObjectID& idRef1);
	friend bool operator==( OvObjectID& idRef0,  OvObjectID& idRef1);

	bool operator==(const OvObjectID& idRef);
	bool operator==(OvObjectID& idRef);

	friend bool operator<(const OvObjectID& idRef0, const OvObjectID& idRef1);
	bool operator<(const OvObjectID& idRef);
	bool operator<(OvObjectID& idRef);

	friend bool operator>(const OvObjectID& idRef0, const OvObjectID& idRef1);
	bool operator>(const OvObjectID& idRef);
	bool operator>(OvObjectID& idRef);
};