#pragma once
#include "OvXComponent.h"
#include "OvPoint3.h"
class NxScene;
class NxActor;
class OxBoxMovement : public OvXComponent
{
public:
	OxBoxMovement(NxScene * scene, OvPoint3& vel );;
	virtual void SetUp() override;
	virtual void ShutDown() override;
	virtual void Update(float _fElapse) override;
private:
	OvPoint3 m_startpt;
	float m_time;
	float m_radian;
	NxActor * m_actor;
	NxScene * m_scene;
	OvPoint3 m_vel;
};