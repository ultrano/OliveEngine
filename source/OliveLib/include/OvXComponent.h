#pragma once
#include "OvRefBase.h"
#include "OvAutoPtr.h"
#include "OvObject.h"


//! 설명
/*
virtual void	Update(OvFloat _fElapse) = 0;
를 재정의 해서 쓰셈
*/
OvREF_POINTER(OvXObject);
OvREF_POINTER(OvXComponent);
class OvXComponent : public OvObject
{
	OvRTTI_DECL(OvXComponent);
public:

	OvXComponent();
	~OvXComponent();

	void			SetTarget(OvXObjectSPtr _pEquippedObject);
	OvXObjectSPtr	GetTarget();

	virtual void	SetUp();
	virtual void	ShutDown();
	virtual void	Update(OvFloat _fElapse) = 0;

	void			SetName( const OvString& name);
	const OvString&	GetName();

private:

	OvXObject*		m_equippedObject;
	OvString		m_name;

};