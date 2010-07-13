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

	virtual void	UpdateSubordinate(float _fElapse);

	void AttachChild(OvXObjectSPtr _pObject);

	// ����� �������ٸ�, ������ ��ü�� ���� �����͸� �����Ѵ�.
	OvXObjectSPtr	DettachChild(OvXObjectSPtr _pObject);

	size_t			GetChildCount();

	OvXObjectSPtr	GetChildeAt( unsigned int iIndex);

private:


	OvObjectCollector	m_clectrChildCollect;

};