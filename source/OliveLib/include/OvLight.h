#pragma once
#include "OvSceneEffector.h"

class OvLight : public OvSceneEffector
{
	OvRTTI_DECL(OvLight);
};

class OvPointLight : public OvLight 
{
	OvRTTI_DECL( OvPointLight );

public:

private:

	OvFloat m_startLight;
	OvFloat m_endLight;

};