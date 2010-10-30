#pragma once
#include "OvRefBase.h"
#include "OvBitFlags.h"

OvREF_POINTER(OvResource);
class OvResource : public OvRefBase
{
	OvRTTI_DECL(OvResource);
public:

	OvResource();
	~OvResource();

};

