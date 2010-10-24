#pragma once


class OxTestPhysx
{
public:
	OxTestPhysx();
	~OxTestPhysx();

	NxScene*	GetScene();

private:
	NxPhysicsSDK*	m_physicsSDK;
	NxScene*		m_scene;
};