#pragma once
#include "OvMemObject.h"
#include "OvUtility_RTTI.h"

class OvInterpMethod : public OvMemObject
{
	OvRTTI_DECL_ROOT( OvInterpMethod );

public:

	virtual float Interpolating( float src, float dest) = 0;

private:

};