#include "OvXNode.h"
#include "OliveValue.h"
#include "OvObjectOutputStream.h"
using namespace std;


OvRTTI_IMPL(OvXNode);

OvFACTORY_OBJECT_IMPL(OvXNode);

OvXNode::OvXNode()
{
	
}

OvXNode::~OvXNode()
{
	m_children.clear();
}

void OvXNode::_update_system( OvFloat _fElapse )
{
	//! �ڽ��� ������Ʈ�� �ڽ� ����Ʈ���� ������ �ڽ���
	//! ����޶�� ��û�� �Ҽ� �ִ�.
	//! �׷��� �Ǹ� 
	//! ������Ʈ ������ ��ų�� �ֱ� ������
	//! ������Ʈ�ÿ� ī�Ǻ��� �߰� �װɷ� �����̽��z �����Ѵ�.

	OvObjectSet update_copy = m_children;
	for each( OvObjectSPtr child in update_copy )
	{
		OvXObject* xobj = OvCastTo<OvXObject>(child);
		xobj->Update(_fElapse);
	}
}

void OvXNode::AttachChild( OvXObjectSPtr obj )
{

	if(!obj)
	{
		return ;
	}

	// �ڽ� Ȥ�� ������ �ڽ��� �ڽ����� �η��� �õ����� �˻��Ѵ�.
	// �׷��� �Ź����� �õ��޴� ���� ���� ������ ������ ���Ǿ� ������.
	OvXNodeSPtr parentNode = this;
	for ( ; parentNode ; parentNode = parentNode->GetAttachedNode() )
	{
		if ( obj == parentNode )
		{
			return ;
		}
	}

	// ���ϵ������Ʈ�� ã�´�.

	if ( m_children.find(obj) != m_children.end() )
	{
		return ;
	}

	// ���� �θ� �ִٸ� �� �θ𿡰� �� ��ü�� ���� ������ ��û.
	OvXNodeSPtr old_parent = obj->GetAttachedNode();
	if(old_parent)
		old_parent->DettachChild(obj);

	m_children.insert(obj);
	obj->_set_parent(this);
}

OvXObjectSPtr	OvXNode::DettachChild( OvXObjectSPtr obj )
{
	if(!obj)
		return NULL;

	// ���ϵ������Ʈ�� ã�´�.
	if ( m_children.find(obj) == m_children.end() )
		return NULL;

	obj->_set_parent(NULL);
	m_children.erase(obj);

	return obj;
}

size_t			OvXNode::GetChildCount()
{
	return m_children.size();
}

//////////////////////////////////////////////////////////////////////////
//////////////////////////////////////////////////////////////////////////
//////////////////////////////////////////////////////////////////////////


OvRTTI_IMPL(OvSceneNode);


OvFACTORY_OBJECT_IMPL(OvSceneNode);

void OvSceneNode::UpdateScene( OvFloat elapse )
{
	OvXObjectSPtr obj = NULL;
	OvSceneNode* sc_obj = NULL;
	OvObjectSet children;
	if ( GetChildrenSet( children ) )
	{
		for each( obj in children )
		{
			if ( sc_obj = OvCastTo<OvSceneNode>( obj ) )
			{
				sc_obj->SetScene( GetScene() );
			}
		}
	}
}

void OvSceneNode::SetScene( OvScene* scene )
{
	if ( scene )
	{
// 		scene->ListUpSceneNode( this );
// 		m_scene = scene;
	}
}

OvScene* OvSceneNode::GetScene()
{
	return m_scene;
}

OvSize OvXNode::GetChildrenSet( OvObjectSet children )
{
	children = m_children;
	return children.size();
}

void OvXNode::Serialize( OvObjectOutputStream & output )
{
	__super::Serialize( output );

	output.Write( m_children.size() );

	for each( OvObjectSPtr obj in m_children )
	{
		output.WriteObject( obj );
	}
}

void OvXNode::Deserialize( OvObjectInputStream & input )
{
	__super::Deserialize( input );

	OvSize children_count = 0;
	input.Read( children_count );

	while ( children_count-- )
	{
		m_children.insert( input.ReadObject() );
	}
}

