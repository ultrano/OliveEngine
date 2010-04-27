#pragma once
#include "OvXObject.h"

OvREF_POINTER(OvXNode);

class OvXNode : public OvXObject
{
	OvRTTI_DECL(OvXNode);
	OvPROP_BAG_DECL(OvXNode);

public:
	OvXNode();
	virtual ~OvXNode();

	virtual void	UpdateSubordinate(float _fElapse);

	void AttachChild(OvXObjectSPtr _pObject);

	// 제대로 지워졌다면, 지워진 객체에 대한 포인터를 리턴한다.
	OvXObjectSPtr	DettachChild(OvXObjectSPtr _pObject);

	size_t			GetChildCount();

	OvXObjectSPtr	GetChildeAt(int iIndex);

private:
	struct OvPimple;
	OvAutoPtr<OvPimple> m_pPimple;
	class OvProp_Pimple;
};

template<typename Type_0>
OvXObjectSPtr FindLeafObject(OvXObjectSPtr pObject) 
{
	if (pObject)
	{
		if (OvRTTI_IsKindOf(OvCamera,pObject))
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
				if (kpObj&&OvRTTI_IsKindOf(Type_0,kpObj))
				{
					return kpObj;
				}
			}
		}
	}

	return NULL;
}