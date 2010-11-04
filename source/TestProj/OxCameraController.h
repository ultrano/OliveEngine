#pragma once
#include "OvXComponent.h"
#include "OvPoint2.h"

class NxScene;
class NxActor;

class OxCameraController : public OvXComponent
{
public:

	OxCameraController( NxScene * scene );
	~OxCameraController();

	virtual void SetUp() override;
	virtual void ShutDown() override;
	virtual void Update( float _fElapse ) override;
private:
	NxScene * m_scene;
	NxActor * m_cameraActor;
	OvPoint2 m_accumulatedRotate;
	OvPoint2 m_lastMousePos;
	OvPoint2 m_accumMovement;
};