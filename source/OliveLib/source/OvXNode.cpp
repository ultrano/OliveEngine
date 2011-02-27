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
	//! 자식의 업데이트중 자식 리스트에서 임의의 자식을
	//! 때어달라는 요청을 할수 있다.
	//! 그렇게 되면 
	//! 업데이트 순서가 엉킬수 있기 때문에
	//! 업데이트시에 카피본을 뜨고 그걸로 업데이스틑 시행한다.

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

	// 자신 혹은 조상을 자신의 자식으로 두려는 시도인지 검사한다.
	// 그렇게 돼버리면 시도햇던 노드로 부터 하위의 노드들은 고립되어 버린다.
	OvXNodeSPtr parentNode = this;
	for ( ; parentNode ; parentNode = parentNode->GetAttachedNode() )
	{
		if ( obj == parentNode )
		{
			return ;
		}
	}

	// 차일드오브젝트를 찾는다.

	if ( m_children.find(obj) != m_children.end() )
	{
		return ;
	}

	// 기존 부모가 있다면 그 부모에게 이 객체에 대한 삭제를 요청.
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

	// 차일드오브젝트를 찾는다.
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

