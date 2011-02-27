#include "OvXObject.h"
#include "OvXNode.h"
#include "OliveValue.h"
#include "OvXComponent.h"
#include "OvObjectCollector.h"
#include "OvUtility.h"

OvRTTI_IMPL(OvXObject);
OvFACTORY_OBJECT_IMPL(OvXObject);

OvXObject::OvXObject()
:m_parent(NULL)
{
	m_controlFlags.Clear( true );
}
OvXObject::~OvXObject()
{
}

void OvXObject::SetControlFlag( CONTROL_FLAG flag, OvBool check )
{
	m_controlFlags.SetFlag( flag, check );
}

OvBool OvXObject::GetControlFlag( CONTROL_FLAG flag )
{
	return m_controlFlags.GetFlag( flag );
}

void OvXObject::Update(OvFloat _fElapse)
{
	if ( false == GetControlFlag( UPDATABLE ) )
	{
		return ;
	}
	OvTransform&	krLocalTransform = m_tfLocalTransform;
	OvTransform&	krWorldTransform = m_tfWorldTransform;

	m_localBuildMatrix = MakeTransformMatrix( krLocalTransform );

	if (GetAttachedNode())
	{
		OvXNodeSPtr kpParent = GetAttachedNode();
		const OvMatrix&	krParentWorldMatrix = kpParent->GetWorldMatrix();

		m_worldBuildMatrix = m_localBuildMatrix * krParentWorldMatrix;

	}else
	{
		m_worldBuildMatrix	= m_localBuildMatrix;
	}

	m_tfWorldTransform = ExtractTransformFromMatrix( m_worldBuildMatrix );

	OvObjectSet	components = m_components;
	for each( OvObjectSPtr obj in components )
	{
		OvXComponentSPtr comp = OvCastTo<OvXComponent>( obj );
		if ( comp )
		{
			comp->Update( _fElapse );
		}
	}

	UpdateSubordinate(_fElapse);
	_update_system(_fElapse);
}

void OvXObject::UpdateSubordinate( OvFloat _fElapse )
{

}

void	OvXObject::SetTranslate(OvPoint3& _rPosition)
{
	m_tfLocalTransform.Position = _rPosition;
}
void	OvXObject::SetTranslate(OvFloat x,OvFloat y,OvFloat z)
{
	SetTranslate(OvPoint3(x,y,z));
}
void	OvXObject::SetRotation(OvQuaternion& _rRotation)
{
	m_tfLocalTransform.Quaternion = _rRotation;
}
void	OvXObject::SetScale(OvFloat _fScale)
{
	m_tfLocalTransform.Scale = OvPoint3(1,1,1) * _fScale;
}
void	OvXObject::SetScale(const OvPoint3& ptAxisScale)
{
	m_tfLocalTransform.Scale = ptAxisScale;
}

OvPoint3&		OvXObject::GetTranslate()
{
	return m_tfLocalTransform.Position;
}
OvQuaternion&	OvXObject::GetRotation()
{
	return m_tfLocalTransform.Quaternion;
}
const OvPoint3&			OvXObject::GetScale()
{
	return m_tfLocalTransform.Scale;
}

const OvMatrix&	OvXObject::GetLocalMatrix()
{
	return m_localBuildMatrix;
}

void			OvXObject::SetTranslateFromWorldCoord(OvPoint3& _rPosition)
{
	if (GetAttachedNode())
	{
		OvMatrix	kParentMat = GetAttachedNode()->GetWorldMatrix();
		OvMatrix	kResultMat = OvMatrix().Translate(_rPosition) * OvMatrixInverseMatrix(kParentMat);
		SetTranslate( OvMatrixExtractTraslate(kResultMat) );
	}
	else
	{
		SetTranslate(_rPosition);
	}
}

void			OvXObject::SetTranslateFromWorldCoord(OvFloat x,OvFloat y,OvFloat z)
{
	SetTranslateFromWorldCoord(OvPoint3(x,y,z));
}

void			OvXObject::SetRotationFromWorldCoord(OvQuaternion& _rRotation)
{
	if (GetAttachedNode())
	{
		OvMatrix	kParentMat = GetAttachedNode()->GetWorldMatrix();
		OvMatrix	kResultMat = OvMatrix().Rotate(_rRotation) * OvMatrixInverseMatrix(kParentMat);
		SetRotation( OvMatrixExtractRotate(kResultMat) );
	}
	else
	{
		SetRotation(_rRotation);
	}
}

void			OvXObject::SetScaleFromWorldCoord(OvPoint3& _rScale)
{
	if (GetAttachedNode())
	{
		OvMatrix	kParentMat = GetAttachedNode()->GetWorldMatrix();
		OvMatrix	kResultMat = OvMatrix().Scale(_rScale) * OvMatrixInverseMatrix(kParentMat);
		SetScale( OvMatrixExtractScale(kResultMat) );
	}
	else
	{
		SetScale(_rScale);
	}
}

void			OvXObject::SetScaleFromWorldCoord(OvFloat _fScale)
{
	SetScaleFromWorldCoord(OvPoint3(_fScale,_fScale,_fScale));
}

const OvPoint3&		OvXObject::GetWorldTranslate()
{
	return m_tfWorldTransform.Position;
}
const OvQuaternion&	OvXObject::GetWorldRotation()
{
	return m_tfWorldTransform.Quaternion;
}
const OvPoint3&			OvXObject::GetWorldScale()
{
	return m_tfWorldTransform.Scale;
}
const OvMatrix&		OvXObject::GetWorldMatrix()
{
	return m_worldBuildMatrix;
}

OvBool OvXObject::IsNode()
{
	return ( OvIsKindOf< OvXNode >( this ) != NULL );
}

OvBool OvXObject::IsLeaf()
{
	return ! IsNode();
}


void	OvXObject::_set_parent(OvXNodeSPtr _pParentNode)
{
	m_parent = _pParentNode.GetRear();
}

OvXNodeSPtr	OvXObject::GetAttachedNode()
{
	return m_parent;
}


OvBool	OvXObject::GetComponents( OvObjectSet& components )
{
	components = m_components;
	return !!components.size();
};

OvBool	OvXObject::_equip_component( OvXComponentSPtr component )
{
	if( component && component->GetTarget() == this )
	{
		component->SetUp();
		m_components.insert( component );
		return true;
	}
	return false;
};

OvBool OvXObject::_remove_component( OvXComponentSPtr component )
{
	if( component && component->GetTarget() == this )
	{
		component->ShutDown();
		m_components.erase( component );
		return true;
	}
	return false;
}

void OvXObject::_update_system( OvFloat _fElapse )
{

}

OvXComponentSPtr OvXObject::RemoveComponent( const OvObjectSPtr obj )
{
	if ( OvXComponent* comp = OvCastTo<OvXComponent>( obj ) )
	{
		if ( m_components.find( comp ) != m_components.end() )
		{
			m_components.erase( comp );
			comp->SetTarget( NULL );
			return comp;
		}
	}
	return NULL;
}
OvXComponentSPtr OvXObject::RemoveComponent( const OvObjectID& objID )
{
	for each( OvObjectSPtr obj in m_components )
	{
		if ( obj->GetObjectID() == objID )
		{
			m_components.erase( obj );
			return obj;
		}
	}
	return NULL;
}

OvXComponentSPtr OvXObject::RemoveComponent( const OvString& name )
{
	for each( OvObjectSPtr obj in m_components )
	{
		OvXComponent* comp = OvCastTo<OvXComponent>( obj );
		if ( comp->GetName() == name )
		{
			m_components.erase( obj );
			return obj;
		}
	}
	return NULL;
}

void OvXObject::Serialize( OvObjectOutputStream & output )
{
	__super::Serialize( output );

	output.WriteObject( m_parent );
	output.Write( m_cCullingSphere );
	output.Write( m_tfLocalTransform );
	output.Write( m_localBuildMatrix );

	output.Write( m_tfWorldTransform );
	output.Write( m_worldBuildMatrix );

	output.Write( m_controlFlags );

	output.Write( m_components.size() );
	for each ( OvObjectSPtr obj in m_components )
	{
		output.WriteObject( obj );
	}

}

void OvXObject::Deserialize( OvObjectInputStream & input )
{
	__super::Deserialize( input );

	m_parent = (OvXNode*)input.ReadObject();
	input.Read( m_cCullingSphere );
	input.Read( m_tfLocalTransform );
	input.Read( m_localBuildMatrix );

	input.Read( m_tfWorldTransform );
	input.Read( m_worldBuildMatrix );

	input.Read( m_controlFlags );

	OvSize comp_count = 0;
	input.Read( comp_count );
	while ( comp_count--  )
	{
		m_components.insert( input.ReadObject() );
	}
}
