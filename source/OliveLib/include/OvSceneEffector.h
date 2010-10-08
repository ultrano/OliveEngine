#pragma once
#include "OvXNode.h"

class OvScene;
class OvSceneEffector : public OvXNode
{
	OvRTTI_DECL(OvSceneEffector);

	virtual void	PrepareEffect(OvScene * scene ) = 0;
};