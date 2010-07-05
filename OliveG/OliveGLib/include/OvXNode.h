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

	OvXObjectSPtr	GetChildeAt(int iIndex);

private:

	OvObjectCollector	m_clectrChildCollect;

};

template<typename Type_0>
OvXObjectSPtr FindLeafObject(OvXObjectSPtr pObject) 
{
	if (pObject)
	{
		if (OvRTTI_Util::IsKindOf<Type_0>(pObject))
		{
			return pObject;
		}
		if (pObject->IsNode())
		{
			OvXNodeSPtr kpParent = pObject;
			int iChildCount = kpParent->GetChildCount();
			for (int i = 0 ; i < iChildCount ; ++i)
			{
				OvXObjectSPtr kpObj = kpParent->GetChildeAt(i);
				if ( kpObj && OvRTTI_Util::IsKindOf< Type_0 >( kpObj ) )
				{
					return kpObj;
				}
			}
		}
	}

	return NULL;
}