#include "OvXNode.h"
#include <list>
#include <algorithm>
#include "OvProperty.h"
using namespace std;

OvRTTI_IMPL(OvXNode);

OvPROPERTY_BAG_BEGIN(OvXNode);
OvPROPERTY_BAG_END(OvXNode);



OvXNode::OvXNode()
{
	
}

OvXNode::~OvXNode()
{
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

	// ���ϵ������Ʈ�� ã�´�.
	if (m_clectrChildCollect.IsCollected(_pObject))
		return ;

	// ���� �θ� �ִٸ� �� �θ𿡰� �� ��ü�� ���� ������ ��û.
	OvXNodeSPtr kpParentNode = _pObject->GetParent();
	if(kpParentNode)
		kpParentNode->DettachChild(_pObject);

	m_clectrChildCollect.AddObject(_pObject);
	_pObject->SetParent(this);
}

OvXObjectSPtr	OvXNode::DettachChild(OvXObjectSPtr _pObject)
{
	if(!_pObject)
		return NULL;

	// ���ϵ������Ʈ�� ã�´�.
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
	
	return m_clectrChildCollect.GetByAt(iIndex);
}
