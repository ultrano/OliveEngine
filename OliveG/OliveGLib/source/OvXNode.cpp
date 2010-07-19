#include "OvXNode.h"
#include <list>
#include <algorithm>
#include "OvRegisterableProperties.h"
#include "OliveValue.h"
using namespace std;


OvRTTI_IMPL(OvXNode);

OvPROPERTY_BAG_BEGIN(OvXNode);
	OvPROPERTY_BAG_REGISTER(OvProp_object_collector,m_clectrChildCollect);
OvPROPERTY_BAG_END(OvXNode);



OvXNode::OvXNode()
{
	
}

OvXNode::~OvXNode()
{
	m_clectrChildCollect.Clear();
}

void	OvXNode::UpdateSubordinate(float _fElapse)
{
	__super::UpdateSubordinate(_fElapse);

	for (int i=0;i<m_clectrChildCollect.Count();++i)
	{
		OvXObjectSPtr kpChild = m_clectrChildCollect.GetByAt(i);
		kpChild->Update(_fElapse);
	}

}

void OvXNode::AttachChild(OvXObjectSPtr _pObject)
{
	if(!_pObject)
		return ;

	// 차일드오브젝트를 찾는다.
	if (m_clectrChildCollect.IsCollected(_pObject))
		return ;

	// 기존 부모가 있다면 그 부모에게 이 객체에 대한 삭제를 요청.
	OvXNodeSPtr kpParentNode = _pObject->GetAttachedNode();
	if(kpParentNode)
		kpParentNode->DettachChild(_pObject);

	m_clectrChildCollect.AddObject(_pObject);
	_pObject->SetParent(this);
}

OvXObjectSPtr	OvXNode::DettachChild(OvXObjectSPtr _pObject)
{
	if(!_pObject)
		return NULL;

	// 차일드오브젝트를 찾는다.
	if (m_clectrChildCollect.IsCollected(_pObject) == false)
		return NULL;

	_pObject->SetParent(NULL);
	m_clectrChildCollect.RemoveObject(_pObject);

	return _pObject;
}

size_t			OvXNode::GetChildCount()
{
	return m_clectrChildCollect.Count();
}

OvXObjectSPtr	OvXNode::GetChildeAt(unsigned int iIndex)
{
	if (0 > iIndex)
	{
		return NULL;
	}
	if (iIndex >= GetChildCount())
	{
		return NULL;
	}
	
	return m_clectrChildCollect.GetByAt(iIndex);
}