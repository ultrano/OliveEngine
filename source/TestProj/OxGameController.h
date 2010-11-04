#pragma once
#include "OvXComponent.h"

class OxGameController : public OvXComponent
{
	virtual void SetUp() override;
	virtual void ShutDown() override;
	virtual void Update( float _fElapse ) override;
};