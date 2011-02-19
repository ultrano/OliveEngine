#pragma once
#include "OvTypeDef.h"
#include "OvUtility_RTTI.h"
#include "OvRefBase.h"

interface_class OvOutputStream : public OvRefBase
{
	OvRTTI_DECL_ROOT(OvOutputStream);

	virtual OvBool WriteByte( OvByte write ) = 0;
	virtual OvSize WriteBytes( OvByte * write_buf, OvSize write_size ) = 0;

};