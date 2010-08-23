#pragma once
#include "OvXComponent.h"
#include "OvPoint3.h"
OvREF_POINTER(GMPhysics);
class GMPhysics : public OvXComponent
{
	OvRTTI_DECL( GMPhysics );

public:

	virtual void	SetUp() override;
	virtual void	ShutDown() override;
	virtual void	Update(float _fElapse) override;

protected:

	void	_gravity( float _fElapse );
	void	_repulsion( float _fElapse );
	void	_friction( float _fElapse );

	OvPoint3	_refection( OvPoint3 inject, OvPoint3 norm );

private:

};