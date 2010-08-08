#pragma once
#include "OvXComponent.h"

class OvPoint3;
class OvQuaternion;
OvREF_POINTER(OvRotateTable);
OvREF_POINTER(OvTranslateTable);

OvREF_POINTER(OvTransformController)
class OvTransformController : public OvXComponent
{
public:
	OvTransformController();
	~OvTransformController();

	void			AddPosKey(float fTick,const OvPoint3& crPos);

	void			SetRotateTable(OvRotateTableSPtr pRotateTable);
	void			SetTranslateTable(OvTranslateTableSPtr pTranslateTable);

	float			GetTickCount();

	//
	void			SetStartTick(float fTick);
	void			SetEndTick(float fTick);
	float			GetStartTick();
	float			GetEndTick();
	//

	virtual void	Update(float _fElapse);

	void			UpdateRot();
	void			UpdatePos();

	void			CommitTransform();

private:

	struct OvPimple;
	OvAutoPtr<OvPimple> m_pPimple;
};