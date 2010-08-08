#pragma once
#include "OvXObject.h"
#include "OvObjectCollector.h"

OvREF_POINTER(OvXNode);
class OvStorage;
class OvXNode : public OvXObject
{
	OvRTTI_DECL(OvXNode);
	OvPROPERTY_BAG_DECL(OvXNode);

public:

	OvXNode();
	virtual ~OvXNode();

	void AttachChild(OvXObjectSPtr _pObject);

	// 제대로 지워졌다면, 지워진 객체에 대한 포인터를 리턴한다.
	OvXObjectSPtr	DettachChild(OvXObjectSPtr _pObject);

	size_t			GetChildCount();

	OvXObjectSPtr	GetChildeAt( unsigned int iIndex);
private:

	virtual void	_update_system( float _fElapse ) override;

private:


	OvObjectCollector	m_clectrChildCollect;

};