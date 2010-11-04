#include "OvResource.h"
#include "OvResourceManager.h"

OvRTTI_IMPL(OvResource);

OvResource::OvResource()
{
	OvResourceManager::GetInstance()->_called_when_resource_created( this );
}

OvResource::~OvResource()
{
	OvResourceManager::GetInstance()->_called_when_resource_deleted( this );
}
