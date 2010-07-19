#pragma once
#include "OvLight.h"


class OvPointLight : public OvLight
{
	OvRTTI_DECL(OvPointLight);

	virtual void	PrepareRender(OvXObjectSPtr affect) {};


};