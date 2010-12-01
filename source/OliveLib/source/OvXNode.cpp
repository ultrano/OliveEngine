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

OvFACTORY_OBJECT_IMPL(OvXNode);

OvXNode::OvXNode()
{
	
}

OvXNode::~OvXNode()
{
	m_clectrChildCollect.Clear();
}

void OvXNode::_update_system( float _fElapse )
{
	//! �ڽ��� ������Ʈ�� �ڽ� ����Ʈ���� ������ �ڽ���
	//! ����޶�� ��û�� �Ҽ� �ִ�.
	//! �׷��� �Ǹ� 
	//! ������Ʈ ������ ��ų�� �ֱ� ������
	//! ������Ʈ�ÿ� ī�Ǻ��� �߰� �װɷ� �����̽��z �����Ѵ�.

	OvObjectCollector update_copy = m_clectrChildCollect;
	for ( unsigned i = 0 ; i < update_copy.Count() ; ++i )
	{
		OvXObjectSPtr child = update_copy.GetByAt(i);
		child->Update(_fElapse);
	}
}

void OvXNode::AttachChild( OvXObjectSPtr _pObject )
{

	if(!_pObject)
	{
		return ;
	}

	// �ڽ� Ȥ�� ������ �ڽ��� �ڽ����� �η��� �õ����� �˻��Ѵ�.
	// �׷��� �Ź����� �õ��޴� ���� ���� ������ ������ ���Ǿ� ������.
	OvXNodeSPtr parentNode = this;
	for ( ; parentNode ; parentNode = parentNode->GetAttachedNode() )
	{
		if ( _pObject == parentNode )
		{
			return ;
		}
	}

	// ���ϵ������Ʈ�� ã�´�.
	if (m_clectrChildCollect.IsCollected(_pObject))
	{
		return ;
	}

	// ���� �θ� �ִٸ� �� �θ𿡰� �� ��ü�� ���� ������ ��û.
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

	// ���ϵ������Ʈ�� ã�´�.
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

OvXObjectSPtr	OvXNode::GetChildeAt(OvUInt iIndex)
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