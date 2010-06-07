#pragma once
#include "OvRefBase.h"
#include "OvAutoPtr.h"
#include "OvObject.h"
// class 선선언부
OvREF_POINTER(OvXObject);
//



//! 설명
/*
virtual void	Update(float _fElapse) = 0;
를 재정의 해서 쓰셈
*/
OvREF_POINTER(OvXController);
class OvXController : public OvObject
{
	OvRTTI_DECL(OvXController);
public:

	OvXController();
	~OvXController();

	void					SetNextController(OvXObjectSPtr _pNextController);
	OvXObjectSPtr			GetNextController();

	void					SetTargetObject(OvXObjectSPtr _pTargetObject);
	OvXObjectSPtr			GetTargetObject();

	virtual void	Update(float _fElapse) = 0;

private:

	struct OvPimple;
	OvAutoPtr<OvPimple> m_pPimple;
};