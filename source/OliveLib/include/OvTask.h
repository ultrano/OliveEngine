#pragma once
#include "OvMemObject.h"
#include "OvTypeDef.h"

class OvTask : public OvMemObject
{
	OvTask( const OvString& name );
	virtual ~OvTask();
private:
	OvString m_name;
};