#pragma once
#include "OvXNode.h"

class OvRenderEffector : public OvXNode
{
	OvRTTI_DECL(OvRenderEffector);

	virtual void	PrepareRender(OvXObjectSPtr affect) = 0;
};