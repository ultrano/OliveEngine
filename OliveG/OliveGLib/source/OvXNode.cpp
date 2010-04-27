#include "OvXNode.h"
#include <list>
#include <algorithm>
#include "OvObjectCollector.h"
#include "OvProperty.h"
using namespace std;

OvRTTI_IMPL_PROP(OvXNode,OvXObject);
OvPROP_BAG_IMPL(OvXNode);
struct OvXNode::OvPimple : OvMemObject
{
	OvObjectCollector	m_listChildCollect;
};

OvXNode::OvXNode():m_pPimple(new OvXNode::OvPimple)
{
	
}

class OvXNode::OvProp_Pimple : public OvProperty
{
	virtual bool	Store(OvObject* pObj, TiXmlElement& rXml)
	{
		OvXNode::OvPimple* kpProp = (OvXNode::OvPimple*)Access(pObj);
		int kiCount = kpProp->m_listChildCollect.Count();
		return false;
	};
	virtual bool	Restore(OvObject* pObj, TiXmlElement& rXml){return false;};
};

void OvXNode::RegisterProperties()
{
	{
		OvProp_Pimple* kpPropProtector = new OvProp_Pimple;
		kpPropProtector->SetOffset(offsetof(__this_class,m_pPimple));
		kpPropProtector->SetPropertyName("Protected");
		GetPropertyBag()->RegisterProperty(kpPropProtector);
	}
};


OvXNode::~OvXNode()
{
	m_pPimple = NULL;
}

void	OvXNode::UpdateSubordinate(float _fElapse)
{
	__super::UpdateSubordinate(_fElapse);

	for (int i=0;i<m_pPimple->m_listChildCollect.Count();++i)
	{
		OvXObjectSPtr kpChild = m_pPimple->m_listChildCollect.GetByAt(i);
		kpChild->Update(_fElapse);
	}

}

void OvXNode::AttachChild(OvXObjectSPtr _pObject)
{
	if(!_pObject)
		return ;

	// 차일드오브젝트를 찾는다.
	if (m_pPimple->m_listChildCollect.IsCollected(_pObject))
		return ;

	// 기존 부모가 있다면 그 부모에게 이 객체에 대한 삭제를 요청.
	OvXNodeSPtr kpParentNode = _pObject->GetParent();
	if(kpParentNode)
		kpParentNode->DettachChild(_pObject);

	m_pPimple->m_listChildCollect.AddObject(_pObject);
	_pObject->SetParent(this);
}

OvXObjectSPtr	OvXNode::DettachChild(OvXObjectSPtr _pObject)
{
	if(!_pObject)
		return NULL;

	// 차일드오브젝트를 찾는다.
	if (m_pPimple->m_listChildCollect.IsCollected(_pObject) == false)
		return NULL;

	_pObject->SetParent(NULL);
	m_pPimple->m_listChildCollect.RemoveObject(_pObject);

	return _pObject;
}

size_t			OvXNode::GetChildCount()
{
	return m_pPimple->m_listChildCollect.Count();
}

OvXObjectSPtr	OvXNode::GetChildeAt(int iIndex)
{
	if (0 > iIndex)
	{
		return NULL;
	}
	if (iIndex >= GetChildCount())
	{
		return NULL;
	}
	
	return m_pPimple->m_listChildCollect.GetByAt(iIndex);
}
