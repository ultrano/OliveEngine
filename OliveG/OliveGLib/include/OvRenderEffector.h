#pragma once
#include "OvXObject.h"

class OvRenderEffector : public OvXObject
{
	OvRTTI_DECL(OvRenderEffector);

	virtual void	PrepareRender(OvXObjectSPtr affect) = 0;
};