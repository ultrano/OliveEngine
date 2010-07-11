#include "OvResource.h"

OvRTTI_IMPL(OvResource);

OvResource::OvResource()
{
}

OvResource::~OvResource()
{
}

const string& OvResource::GetResourceLocation() const
{
	return m_fileLocation;
}