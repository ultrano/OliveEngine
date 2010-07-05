#include "OvXObject.h"
#include "OvXNode.h"
#include "OvXComponent.h"
#include "OvObjectCollector.h"
#include "OvStringUtility.h"
#include "OvProperty.h"
#include "OvRegisterableProperties.h"

OvRTTI_IMPL(OvXObject);
OvPROPERTY_BAG_BEGIN(OvXObject);
	OvDECLARE_PROPERTY( OvProp_object_pointer, m_pParent );
	OvDECLARE_PROPERTY( OvProp_float3,  m_tfLocalTransform.Scale );
	OvDECLARE_PROPERTY( OvProp_float3,  m_tfLocalTransform.Position );
	OvDECLARE_PROPERTY( OvProp_float4,  m_tfLocalTransform.Quaternion );
	OvDECLARE_PROPERTY( OvProp_object_collector,  m_extraComponents );
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

	if (GetParent())
	{
		OvXNodeSPtr kpParent = GetParent();
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

	UpdateSubordinate(_fElapse);
}

void	OvXObject::UpdateSubordinate(float _fElapse)
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
	if (GetParent())
	{
		OvMatrix	kParentMat = GetParent()->GetWorldMatrix();
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
	if (GetParent())
	{
		OvMatrix	kParentMat = GetParent()->GetWorldMatrix();
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
	if (GetParent())
	{
		OvMatrix	kParentMat = GetParent()->GetWorldMatrix();
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


void	OvXObject::SetParent(OvXNodeSPtr _pParentNode)
{
	m_pParent = _pParentNode.GetRear();
}

OvXObjectSPtr	OvXObject::GetParent()
{
	return m_pParent;
}


bool	OvXObject::GetExtraComponents( OvObjectCollector& extraComponents )
{
	return extraComponents.AddObject( m_extraComponents );
};

bool	OvXObject::EquipExtraComponent( OvXComponentSPtr extraComponent )
{
	if( extraComponent && extraComponent->GetEquippedTarget() == this )
	{
		return m_extraComponents.AddObject( extraComponent );
	}
	return false;
};
