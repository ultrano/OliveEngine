#pragma once
#include "OvTypeDef.h"
#include "OvMemObject.h"

class OvStreamAgent : public OvMemObject
{
	OvBool	Extract();
	OvBool	Inject();
};