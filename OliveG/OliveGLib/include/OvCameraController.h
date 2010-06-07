#pragma once
#include "OvXController.h"

class OvPoint2;
OvREF_POINTER(OvCameraController);
class OvCameraController : public OvXController
{
	OvRTTI_DECL(OvCameraController);

public:

	enum eKeyFlag
	{
		eKeyFlag_Left,
		eKeyFlag_Right,
		eKeyFlag_Up,
		eKeyFlag_Down,
	};

	OvCameraController();
	~OvCameraController();

	void			SetKeyFlag(eKeyFlag eFlag,bool bCheck);
	bool			GetKeyFlag(eKeyFlag eFlag);

	void			SetMouseMoveInterval(OvPoint2& pt2Interval);
	OvPoint2&		GetMouseMoveInterval();

	virtual void	Update(float _fElapse);

private:

	struct OvPimple;
	OvAutoPtr<OvPimple> m_pPimple;

};