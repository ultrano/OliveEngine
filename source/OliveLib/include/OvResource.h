#pragma once
#include "OvRefObject.h"
#include "OvBitFlags.h"

OvREF_POINTER(OvResource);
class OvResource : public OvRefObject
{
	OvRTTI_DECL(OvResource);
public:

	OvResource();
	~OvResource();

};

