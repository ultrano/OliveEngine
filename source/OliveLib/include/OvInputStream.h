#pragma once
#include "OvTypeDef.h"
#include "OvUtility_RTTI.h"
#include "OvRefBase.h"

interface_class OvInputStream : public OvRefBase
{
	OvRTTI_DECL_ROOT(OvInputStream);

	virtual OvBool ReadByte( OvByte & read ) = 0 ;
	virtual OvSize ReadBytes( OvByte * dest, OvSize dest_size ) = 0 ;

};


//////////////////////////////////////////////////////////////////////////
//////////////////////////////////////////////////////////////////////////