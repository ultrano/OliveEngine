#pragma once
#include "OvRenderEffector.h"

class OvLight : public OvRenderEffector
{
	OvRTTI_DECL(OvLight);
};

class OvPointLight : public OvLight 
{
	OvRTTI_DECL( OvPointLight );

public:

private:

	float m_startLight;
	float m_endLight;

};