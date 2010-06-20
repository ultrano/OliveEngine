#pragma once
#include "OvRefBase.h"
#include "OvAutoPtr.h"
#include "OvObject.h"

class OvXObject;

//! 설명
/*
virtual void	Update(float _fElapse) = 0;
를 재정의 해서 쓰셈
*/
OvREF_POINTER(OvXComponent);
class OvXComponent : public OvObject
{
	OvRTTI_DECL(OvXComponent);
	OvPROPERTY_BAG_DECL(OvXComponent);
public:

	OvXComponent();
	~OvXComponent();

	void			SetEquippedTarget(OvXObject* _pEquippedObject);
	OvXObject*		GetEquippedTarget();

	virtual void	Update(float _fElapse) = 0;

private:

	OvXObject*				m_equippedObject;

};