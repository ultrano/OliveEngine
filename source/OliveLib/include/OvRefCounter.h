#pragma once
#include "OvMemObject.h"
#include "OvTypeDef.h"

class OvRefCounter : public OvMemObject
{
	friend class OvRefBase;
private:
	OvRefCounter();
	OvRefCounter( OvRefBase* ptr );
	~OvRefCounter();
	void _delete_this();
public:

	OvUInt	IncRefCount();
	OvUInt	DecRefCount();

	OvUInt	IncWeakCount();
	OvUInt	DecWeakCount();

	OvBool	Expired();

private:
	
	OvUInt	m_ref_count;
	OvUInt	m_weak_count;
	OvRefBase* m_pointer;

};