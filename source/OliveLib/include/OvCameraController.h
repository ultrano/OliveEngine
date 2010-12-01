#pragma once
#include "OvXComponent.h"
#include "OvPoint2.h"
#include "OvPoint3.h"

OvREF_POINTER(OvCameraController)
class OvCameraController : public OvXComponent
{
	OvRTTI_DECL(OvCameraController);
	OvFACTORY_OBJECT_DECL(OvCameraController);
public:
	OvCameraController();
	~OvCameraController();
	virtual void Update(float _fElapse);

private:
	OvPoint2 m_lastMoustPt;
	OvPoint2 m_currentMoustPt;
	OvPoint2 m_moustMoveInterval;
	OvPoint2 m_accumulatedRotate;
	OvPoint2 m_liatMousePos;
};