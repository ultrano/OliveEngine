#pragma once
#include "OvXNode.h"

class OvSingleScene;
class OvSceneEffector : public OvXNode
{
	OvRTTI_DECL(OvSceneEffector);

	virtual void	PrepareEffect(OvSingleScene * scene ) = 0;
};