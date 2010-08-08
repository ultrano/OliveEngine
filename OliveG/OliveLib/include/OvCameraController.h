#pragma once
#include "OvInputEventListener.h"
#include "OvPoint2.h"

OvREF_POINTER(OvCameraController)
class OvCameraController : public OvInputEventListener
{
	OvRTTI_DECL(OvCameraController);
public:
	OvCameraController();
	~OvCameraController();
	virtual bool MessageListen(HWND hwnd, UINT message, WPARAM wparam, LPARAM lparam);

private:
	OvPoint2 m_lastMoustPt;
	OvPoint2 m_currentMoustPt;
	OvPoint2 m_moustMoveInterval;
	OvPoint2 m_accumulatedRotate;
};