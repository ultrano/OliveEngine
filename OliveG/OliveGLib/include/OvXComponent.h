#pragma once
#include "OvRefBase.h"
#include "OvAutoPtr.h"
#include "OvObject.h"


//! ����
/*
virtual void	Update(float _fElapse) = 0;
�� ������ �ؼ� ����
*/
OvREF_POINTER(OvXObject);
OvREF_POINTER(OvXComponent);
class OvXComponent : public OvObject
{
	OvRTTI_DECL(OvXComponent);
	OvPROPERTY_BAG_DECL(OvXComponent);
public:

	OvXComponent();
	~OvXComponent();

	void			SetTarget(OvXObjectSPtr _pEquippedObject);
	OvXObjectSPtr	GetTarget();

	virtual void	Update(float _fElapse) = 0;

private:

	OvXObject*				m_equippedObject;

};