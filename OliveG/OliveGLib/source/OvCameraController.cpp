#include "OvCameraController.h"
#include "OvCamera.h"
#include "OvBitFlags.h"
#include "OvPoint2.h"
#include "OvPoint3.h"
#include "OvQuaternion.h"
#include "OvObjectCollector.h"

OvRTTI_IMPL(OvCameraController,OvXComponent)

struct OvCameraController::OvPimple : OvMemObject
{
	Ov8SetFlags	m_flgKeyFlag;
	OvPoint2	m_pt2MouseMoveInterval;
	OvPoint2	m_pt2AccumulateInterval;
};

OvCameraController::OvCameraController()
:m_pPimple(new OvCameraController::OvPimple)
{

}
OvCameraController::~OvCameraController()
{

}

void	OvCameraController::SetKeyFlag(eKeyFlag eFlag,bool bCheck)
{
	m_pPimple->m_flgKeyFlag.SetFlag(eFlag,bCheck);
}
bool	OvCameraController::GetKeyFlag(eKeyFlag eFlag)
{
	return m_pPimple->m_flgKeyFlag.GetFlag(eFlag);
}
void	OvCameraController::SetMouseMoveInterval(OvPoint2& pt2Interval)
{
	m_pPimple->m_pt2MouseMoveInterval = pt2Interval;
}
OvPoint2&		OvCameraController::GetMouseMoveInterval()
{
	return m_pPimple->m_pt2MouseMoveInterval;
}
void	OvCameraController::Update(float _fElapse)
{
	
	OvCamera*	kpCamera = (OvCamera*)GetEquippedTarget();
	if (kpCamera)
	{
		OvPoint3 kLook = kpCamera->GetWorldLookDirection();
		OvPoint3 kRight = kpCamera->GetWorldRightDirection();
		if (GetKeyFlag(eKeyFlag_Up))
		{
			kpCamera->SetTranslateFromWorldCoord(kpCamera->GetWorldTranslate()+kLook);
		}
		else if (GetKeyFlag(eKeyFlag_Down))
		{
			kpCamera->SetTranslateFromWorldCoord(kpCamera->GetWorldTranslate()-kLook);
		}
		else if (GetKeyFlag(eKeyFlag_Right))
		{
			kpCamera->SetTranslateFromWorldCoord(kpCamera->GetWorldTranslate()+kRight);
		}
		if (GetKeyFlag(eKeyFlag_Left))
		{
			kpCamera->SetTranslateFromWorldCoord(kpCamera->GetWorldTranslate()-kRight);
		}

		if (GetMouseMoveInterval().Length())
		{
			m_pPimple->m_pt2AccumulateInterval += GetMouseMoveInterval();
			float fRotDeltha = 3.14f / 180.f;
			OvQuaternion	kResultQut ;
			kResultQut.Identity();
			kResultQut = kResultQut * OvQuaternion().MakeQuaternion(OvPoint3::AXIS_Y,fRotDeltha*m_pPimple->m_pt2AccumulateInterval.x);
			kResultQut = kResultQut * OvQuaternion().MakeQuaternion(OvPoint3::AXIS_X,fRotDeltha*m_pPimple->m_pt2AccumulateInterval.y);
			kpCamera->SetRotationFromWorldCoord(kResultQut);
			SetMouseMoveInterval(OvPoint2());
		}
		
	}
};