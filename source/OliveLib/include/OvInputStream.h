#pragma once
#include "OvTypeDef.h"
#include "OvUtility_RTTI.h"

interface_class OvInputStream
{
	OvRTTI_DECL_ROOT(OvInputStream);

	virtual OvInputStream& Read( OvString& buf, OvUInt read_size ) = 0 ;
	virtual OvInputStream& ReadLine( OvString& buf )  = 0 ;
};