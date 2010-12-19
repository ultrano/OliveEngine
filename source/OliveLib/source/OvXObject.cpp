#include "OvXObject.h"
#include "OvXNode.h"
#include "OliveValue.h"
#include "OvXComponent.h"
#include "OvObjectCollector.h"
#include "OvStringUtility.h"
#include "OvRegisterableProperties.h"

OvRTTI_IMPL(OvXObject);
OvPROPERTY_BAG_BEGIN(OvXObject);
	OvPROPERTY_BAG_REGISTER( OvPropAccesser_object_pointer, m_pParent );
	OvPROPERTY_BAG_REGISTER( OvPropAccesser_float3,  m_tfLocalTransform.Scale );
	OvPROPERTY_BAG_REGISTER( OvPropAccesser_float3,  m_tfLocalTransform.Position );
	OvPROPERTY_BAG_REGISTER( OvPropAccesser_float4,  m_tfLocalTransform.Quaternion );
	OvPROPERTY_BAG_REGISTER( OvPropAccesser_object_collector,  m_extraComponents );
OvPROPERTY_BAG_END(OvXObject);

OvXObject::OvXObject()
:m_pParent(NULL)
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

	OvObjectCollector	extraComponents = m_extraComponents;
	for ( unsigned i = 0 ; i < extraComponents.Count() ; ++i )
	{
		OvXComponentSPtr component = extraComponents.GetByAt( i );
		if ( component )
		{
			component->Update( _fElapse );
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
	m_pParent = _pParentNode.GetRear();
}

OvXNodeSPtr	OvXObject::GetAttachedNode()
{
	return m_pParent;
}


OvBool	OvXObject::GetComponents( OvObjectCollector& extraComponents )
{
	return extraComponents.AddObject( m_extraComponents );
};

OvBool	OvXObject::_equip_component( OvXComponentSPtr component )
{
	if( component && component->GetTarget() == this )
	{
		component->SetUp();
		return m_extraComponents.AddObject( component );
	}
	return false;
};

OvBool OvXObject::_remove_component( OvXComponentSPtr component )
{
	if( component && component->GetTarget() == this )
	{
		component->ShutDown();
		return m_extraComponents.RemoveObject( component );
	}
	return false;
}

void OvXObject::_update_system( OvFloat _fElapse )
{

}

OvXComponentSPtr OvXObject::RemoveComponent( const OvObjectSPtr component )
{
	if ( component )
	{
		OvXComponentSPtr removedComponent = m_extraComponents.RemoveObject( component );
		removedComponent->SetTarget( NULL );
		return removedComponent;
	}
	return NULL;
}
OvXComponentSPtr OvXObject::RemoveComponent( const OvObjectID& compoentID )
{
	OvXComponentSPtr removedComponent = m_extraComponents.RemoveObject( compoentID );
	removedComponent->SetTarget( NULL );
	return removedComponent;
}

OvXComponentSPtr OvXObject::RemoveComponent( const OvChar* name )
{
	if ( NULL == name ) return NULL;
	OvXComponentSPtr removedComponent = NULL;
	for ( unsigned i = 0 ; i < m_extraComponents.Count() ; ++i )
	{
		removedComponent = m_extraComponents.GetByAt( i );
		if ( removedComponent->GetName() == OvString( name ) )
		{
			removedComponent->SetTarget( NULL );
			return removedComponent;
		}
	}
	return NULL;
}