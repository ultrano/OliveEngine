#pragma once
#include "OvObject.h"
#include "OvInterpMethod.h"

class OvInterpolator : public OvObject
{
	OvRTTI_DECL( OvInterpolator );
public:

private:
	OvInterpMethod* m_interpMethod;
};