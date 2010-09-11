#include "OvXNode.h"
#include <list>
#include <algorithm>
#include "OvRegisterableProperties.h"
#include "OliveValue.h"
using namespace std;


OvRTTI_IMPL(OvXNode);

OvPROPERTY_BAG_BEGIN(OvXNode);
	OvPROPERTY_BAG_REGISTER(OvPropAccesser_object_collector,m_clectrChildCollect);
OvPROPERTY_BAG_END(OvXNode);



OvXNode::OvXNode()
{
	
}

OvXNode::~OvXNode()
{
	m_clectrChildCollect.Clear();
}

void OvXNode::_update_system( float _fElapse )
{
	for (int i=0;i<m_clectrChildCollect.Count();++i)
	{
		OvXObjectSPtr kpChild = m_clectrChildCollect.GetByAt(i);
		kpChild->Update(_fElapse);
	}
}

void OvXNode::AttachChild( OvXObjectSPtr _pObject )
{

	if(!_pObject)
	{
		return ;
	}

	// 자신 혹은 조상을 자신의 자식으로 두려는 시도인지 검사한다.
	// 그렇게 돼버리면 시도햇던 노드로 부터 하위의 노드들은 고립되어 버린다.
	OvXNodeSPtr parentNode = this;
	for ( ; parentNode ; parentNode = parentNode->GetAttachedNode() )
	{
		if ( _pObject == parentNode )
		{
			return ;
		}
	}

	// 차일드오브젝트를 찾는다.
	if (m_clectrChildCollect.IsCollected(_pObject))
	{
		return ;
	}

	// 기존 부모가 있다면 그 부모에게 이 객체에 대한 삭제를 요청.
	OvXNodeSPtr kpParentNode = _pObject->GetAttachedNode();
	if(kpParentNode)
		kpParentNode->DettachChild(_pObject);

	m_clectrChildCollect.AddObject(_pObject);
	_pObject->_set_parent(this);
}

OvXObjectSPtr	OvXNode::DettachChild(OvXObjectSPtr _pObject)
{
	if(!_pObject)
		return NULL;

	// 차일드오브젝트를 찾는다.
	if (m_clectrChildCollect.IsCollected(_pObject) == false)
		return NULL;

	_pObject->_set_parent(NULL);
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