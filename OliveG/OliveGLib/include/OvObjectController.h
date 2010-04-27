#pragma once
#include "OvRefBase.h"
#include "OvAutoPtr.h"
// class �������
OvREF_POINTER(OvXObject);
//



//! ����
/*
virtual void	Update(float _fElapse) = 0;
�� ������ �ؼ� ����
*/
OvREF_POINTER(OvObjectController);
class OvObjectController : public OvRefBase
{

public:

	OvObjectController();
	~OvObjectController();

	void					SetNextController(OvXObjectSPtr _pNextController);
	OvXObjectSPtr			GetNextController();

	void					SetTargetObject(OvXObjectSPtr _pTargetObject);
	OvXObjectSPtr			GetTargetObject();

	virtual void	Update(float _fElapse) = 0;

private:

	struct OvPimple;
	OvAutoPtr<OvPimple> m_pPimple;
};