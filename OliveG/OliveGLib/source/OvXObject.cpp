#include "OvXObject.h"
#include "OvXNode.h"
#include "OvXController.h"
#include "OvXController.h"
#include "OvStringUtility.h"
#include "OvProperty.h"
#include "OvRegisterableProperties.h"

OvRTTI_IMPL_PROP(OvXObject,OvObject);
OvPROP_BAG_IMPL(OvXObject);


void OvXObject::RegisterProperties()
{
	OvProperty* kpProp = NULL;

	kpProp = new OvProp_float3;
	kpProp->SetOffset(offsetof(__this_class,m_tfLocalTransform.Scale));
	kpProp->SetPropertyName("m_tfLocalTransform.Scale");
	GetPropertyBag()->RegisterProperty(kpProp);

	kpProp = new OvProp_float3;
	kpProp->SetOffset(offsetof(__this_class,m_tfLocalTransform.Position));
	kpProp->SetPropertyName("m_tfLocalTransform.Position");
	GetPropertyBag()->RegisterProperty(kpProp);

	kpProp = new OvProp_float4;
	kpProp->SetOffset(offsetof(__this_class,m_tfLocalTransform.Quaternion));
	kpProp->SetPropertyName("m_tfLocalTransform.Quaternion");
	GetPropertyBag()->RegisterProperty(kpProp);

};
OvXObject::OvXObject()
{
	m_pParent = NULL;
}
OvXObject::~OvXObject()
{
}

void OvXObject::Update(float _fElapse)
{
	OvTransform&	krLocalTransform = m_tfLocalTransform;
	OvTransform&	krWorldTransform = m_tfWorldTransform;

	krLocalTransform.BuildTransformMatrix();

	if (GetParent())
	{
		OvXNodeSPtr kpParent = GetParent();
		const OvTransform&	krParentWorldTransform = kpParent->GetWorldTransform();

		krWorldTransform.BuildMatrix = krLocalTransform.BuildMatrix * krParentWorldTransform.BuildMatrix;

	}else
	{
		krWorldTransform.BuildMatrix	= krLocalTransform.BuildMatrix;
	}

	krWorldTransform.ExtractTransformFromBuildMatrix();

	OvXControllerSPtr	kpController = GetHeaderObjectController();
	for (;kpController;kpController = kpController->GetNextController())
	{
		kpController->Update(_fElapse);
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

void			OvXObject::SetTranslateFromWorldCoord(OvPoint3& _rPosition)
{
	if (GetParent())
	{
		OvMatrix	kParentMat = GetParent()->GetWorldTransform().BuildMatrix;
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
		OvMatrix	kParentMat = GetParent()->GetWorldTransform().BuildMatrix;
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
		OvMatrix	kParentMat = GetParent()->GetWorldTransform().BuildMatrix;
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
	return m_tfWorldTransform.BuildMatrix;
}

const OvTransform&	OvXObject::GetWorldTransform()
{
	return m_tfWorldTransform;
}

bool OvXObject::IsNode()
{
	return OvRTTI_IsKindOf(OvXNode,this);
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


OvXControllerSPtr	OvXObject::GetHeaderObjectController()
{
	return m_spHeaderObjectController;
};

void	OvXObject::PrependObjectController(OvXControllerSPtr _pController)
{
	if(!_pController)
		return ;

	_pController->SetNextController(m_spHeaderObjectController);
	m_spHeaderObjectController = _pController;
};
