#pragma once
#include "OvXComponent.h"

class OvPoint3;

OvREF_POINTER(OvAnimateController)
class OvAnimateController : public OvXComponent
{
public:

	OvAnimateController();
	~OvAnimateController();

	//!
	void			SetPositionControllKey(float fTick,const OvPoint3& crPos);
	void			FindPosSample(float fTick,float& fTickSrc,float& fTickDest,OvPoint3& crPosSrc,OvPoint3& crPosDest);
	float			GetMaxTick();
	float			GetMinTick();
	//!

	virtual void	Update(float _fElapse);

private:

	struct OvPimple;
	OvAutoPtr<OvPimple> m_pPimple;

};