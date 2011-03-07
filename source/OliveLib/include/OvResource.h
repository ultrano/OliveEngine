#pragma once
#include "OvRefObject.h"

OvREF_POINTER(OvResource);
interface_class OvResource : public OvRefObject
{
	OvRTTI_DECL(OvResource);
public:

	OvResource();
	~OvResource();

};

