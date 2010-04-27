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
	// 멤버변수들을 기술한다.
	// 멤버변수또한 되도록 캡슐화 하기 위해 핌플패턴을 적용한다.

	//! 부모 포인터를 스마트 포인터로 들고 있을경우
	//! 부모와 자식이 서로 물고 있는 상황이 발생하게 되며
	//! 이는 약참조 현상을 야기 시킨다.
	//! 메모리매니저에 의해서 프로그램이 종료될때
	//! 일괄 삭제 되게 때문에 메모리 리포트에는 메모리릭이
	//! 발생하지 않는걸로 나오지만, 메모리 상에는 쓰지 않는
	//! 메모리로서 상주하게 되고 이는 프로그램의 처리부하로 이어지게 될 가능성이
	//! 높다. 
	//! 적당한 타협선은 일반포인터로만 물고 있다가 사용할때만 
	//! GetParent()인터페이스를 이용하여 스마트카운팅을 증가 시키는것이다.
	//! 이러면 사용할때는 최소한 삭제에 대해서는 보호를 받을수 있게 된다.
	//! 핸들을 들고 그때그때 find해서 쓰는 방법도 있겠지만, 이는 너무 큰
	//! 오버해드를 동반한다.(너무 크다)
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
