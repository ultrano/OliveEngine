#include "OvXObject.h"
#include "OvXNode.h"
#include "OvSphere.h"
#include "OvTransform.h"
#include "OvObjectController.h"
#include "OvObjectFactory.h"
#include "OvObjectController.h"
#include "OvStringUtility.h"
#include "OvProperty.h"

OvRTTI_IMPL_PROP(OvXObject,OvObject);
OvPROP_BAG_IMPL(OvXObject);


struct OvXObject::OvPimple : OvMemObject
{
	// ����������� ����Ѵ�.
	// ����������� �ǵ��� ĸ��ȭ �ϱ� ���� ���������� �����Ѵ�.

	//! �θ� �����͸� ����Ʈ �����ͷ� ��� �������
	//! �θ�� �ڽ��� ���� ���� �ִ� ��Ȳ�� �߻��ϰ� �Ǹ�
	//! �̴� ������ ������ �߱� ��Ų��.
	//! �޸𸮸Ŵ����� ���ؼ� ���α׷��� ����ɶ�
	//! �ϰ� ���� �ǰ� ������ �޸� ����Ʈ���� �޸𸮸���
	//! �߻����� �ʴ°ɷ� ��������, �޸� �󿡴� ���� �ʴ�
	//! �޸𸮷μ� �����ϰ� �ǰ� �̴� ���α׷��� ó�����Ϸ� �̾����� �� ���ɼ���
	//! ����. 
	//! ������ Ÿ������ �Ϲ������ͷθ� ���� �ִٰ� ����Ҷ��� 
	//! GetParent()�������̽��� �̿��Ͽ� ����Ʈī������ ���� ��Ű�°��̴�.
	//! �̷��� ����Ҷ��� �ּ��� ������ ���ؼ��� ��ȣ�� ������ �ְ� �ȴ�.
	//! �ڵ��� ��� �׶��׶� find�ؼ� ���� ����� �ְ�����, �̴� �ʹ� ū
	//! �����ص带 �����Ѵ�.(�ʹ� ũ��)
	OvXNode*	mParent;

	OvSphere mCullingSphere;

	OvTransform	mLocalTransform;
	OvTransform	mWorldTransform;

	OvObjectControllerSPtr	mHeaderObjectController;
};

class OvXObject::OvProp_Pimple : public OvProperty
{
	virtual bool	Store(OvObject* pObj, TiXmlElement& rXml)
	{
		return false;
	};
	virtual bool	Restore(OvObject* pObj, TiXmlElement& rXml){return false;};
};

void OvXObject::RegisterProperties()
{
	{
		OvProp_Pimple* kpPropProtector = new OvProp_Pimple;
		kpPropProtector->SetOffset(offsetof(__this_class,m_pPimple));
		kpPropProtector->SetPropertyName("Protected");
		GetPropertyBag()->RegisterProperty(kpPropProtector);
	}
};
OvXObject::OvXObject():m_pPimple(OvNew OvPimple)
{
	m_pPimple->mParent = NULL;
}
OvXObject::~OvXObject()
{
	m_pPimple = NULL;
}

void OvXObject::Update(float _fElapse)
{
	OvTransform&	krLocalTransform = m_pPimple->mLocalTransform;
	OvTransform&	krWorldTransform = m_pPimple->mWorldTransform;

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

	OvObjectControllerSPtr	kpController = GetHeaderObjectController();
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
	m_pPimple->mLocalTransform.Position = _rPosition;
}
void	OvXObject::SetTranslate(float x,float y,float z)
{
	SetTranslate(OvPoint3(x,y,z));
}
void	OvXObject::SetRotation(OvQuaternion& _rRotation)
{
	m_pPimple->mLocalTransform.Quaternion = _rRotation;
}
void	OvXObject::SetScale(float _fScale)
{
	m_pPimple->mLocalTransform.Scale = OvPoint3(1,1,1) * _fScale;
}
void	OvXObject::SetScale(const OvPoint3& ptAxisScale)
{
	m_pPimple->mLocalTransform.Scale = ptAxisScale;
}

OvPoint3&		OvXObject::GetTranslate()
{
	return m_pPimple->mLocalTransform.Position;
}
OvQuaternion&	OvXObject::GetRotation()
{
	return m_pPimple->mLocalTransform.Quaternion;
}
const OvPoint3&			OvXObject::GetScale()
{
	return m_pPimple->mLocalTransform.Scale;
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
	return m_pPimple->mWorldTransform.Position;
}
const OvQuaternion&	OvXObject::GetWorldRotation()
{
	return m_pPimple->mWorldTransform.Quaternion;
}
const OvPoint3&			OvXObject::GetWorldScale()
{
	return m_pPimple->mWorldTransform.Scale;
}
const OvMatrix&		OvXObject::GetWorldMatrix()
{
	return m_pPimple->mWorldTransform.BuildMatrix;
}

const OvTransform&	OvXObject::GetWorldTransform()
{
	return m_pPimple->mWorldTransform;
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
	m_pPimple->mParent = _pParentNode.GetRear();
}

OvXObjectSPtr	OvXObject::GetParent()
{
	return m_pPimple->mParent;
}


OvObjectControllerSPtr	OvXObject::GetHeaderObjectController()
{
	return m_pPimple->mHeaderObjectController;
};

void	OvXObject::PrependObjectController(OvObjectControllerSPtr _pController)
{
	if(!_pController)
		return ;

	_pController->SetNextController(m_pPimple->mHeaderObjectController);
	m_pPimple->mHeaderObjectController = _pController;
};
