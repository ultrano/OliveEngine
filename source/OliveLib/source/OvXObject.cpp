#include "OvXObject.h"
#include "OvXNode.h"
#include "OvXComponent.h"
#include "OvObjectCollector.h"
#include "OvStringUtility.h"
#include "OvProperty.h"
#include "OvRegisterableProperties.h"

OvRTTI_IMPL(OvXObject);
OvPROPERTY_BAG_BEGIN(OvXObject);
	OvPROPERTY_BAG_REGISTER( OvProp_object_pointer, m_pParent );
	OvPROPERTY_BAG_REGISTER( OvProp_float3,  m_tfLocalTransform.Scale );
	OvPROPERTY_BAG_REGISTER( OvProp_float3,  m_tfLocalTransform.Position );
	OvPROPERTY_BAG_REGISTER( OvProp_float4,  m_tfLocalTransform.Quaternion );
	OvPROPERTY_BAG_REGISTER( OvProp_object_collector,  m_extraComponents );
OvPROPERTY_BAG_END(OvXObject);

OvXObject::OvXObject()
:m_pParent(NULL)
{
}
OvXObject::~OvXObject()
{
}

void OvXObject::Update(float _fElapse)
{
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

	for (int i = 0 ; i < m_extraComponents.Count() ; ++i)
	{
		OvXComponentSPtr	kpController = m_extraComponents.GetByAt( i );
		if ( kpController )
		{
			kpController->Update(_fElapse);
		}
	}

	for ( int i = 0 ; i < m_extraComponents.Count() ; ++i )
	{
		OvXComponentSPtr component = m_extraComponents.GetByAt( i );
		if ( component )
		{
			component->Update( _fElapse );
		}
	}

	UpdateSubordinate(_fElapse);
	_update_system(_fElapse);
}

void OvXObject::UpdateSubordinate( float _fElapse )
{

}

void	OvXObject::SetTranslate(OvPoint3& _rPosition)
{
	m_tfLocalTransform.Position = _rPosition;
}
void	OvXObject::SetTranslate(float x,float y,float z)
{
	SetTranslate(OvPoint3(x,y,z));
}
void	OvXObject::SetRotation(OvQuaternion& _rRotation)
{
	m_tfLocalTransform.Quaternion = _rRotation;
}
void	OvXObject::SetScale(float _fScale)
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

void			OvXObject::SetTranslateFromWorldCoord(float x,float y,float z)
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

void			OvXObject::SetScaleFromWorldCoord(float _fScale)
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

bool OvXObject::IsNode()
{
	return OvRTTI_Util::IsKindOf< OvXNode >( this );
}

bool OvXObject::IsLeaf()
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


bool	OvXObject::GetComponents( OvObjectCollector& extraComponents )
{
	return extraComponents.AddObject( m_extraComponents );
};

bool	OvXObject::_equip_component( OvXComponentSPtr component )
{
	if( component && component->GetTarget() == this )
	{
		return m_extraComponents.AddObject( component );
	}
	return false;
};

bool OvXObject::_remove_component( OvXComponentSPtr component )
{
	if( component && component->GetTarget() == this )
	{
		return m_extraComponents.RemoveObject( component );
	}
	return false;
}

void OvXObject::_update_system( float _fElapse )
{

}

OvXComponentSPtr OvXObject::RemoveComponent( const OvObjectSPtr component )
{
	OvXComponentSPtr removedComponent = m_extraComponents.RemoveObject( component );
	removedComponent->SetTarget( NULL );
	return removedComponent;
}
OvXComponentSPtr OvXObject::RemoveComponent( const OvObjectID& compoentID )
{
	OvXComponentSPtr removedComponent = m_extraComponents.RemoveObject( compoentID );
	removedComponent->SetTarget( NULL );
	return removedComponent;
}