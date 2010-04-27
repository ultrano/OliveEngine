#include "OvCamera.h"
#include "OvTransform.h"
#include "OvRenderer.h"
#include <d3dx9.h>

OvRTTI_IMPL(OvCamera,OvXObject);

struct OvCamera::OvPimple : OvMemObject
{
	OvPoint3	mLookDirection;
	OvPoint3	mUpDirection;
	OvPoint3	mRightDirection;

	OvMatrix	mViewMatrix;
	OvMatrix	mProjectMatrix;

	OvXObjectSPtr mLookTarget;

	eCameraType	mType;
	float		mFOV;
	float		mNearClip;
	float		mFarClip;
};

OvCamera::OvCamera():m_pPimple(OvNew OvPimple)
{
	memset(m_pPimple.GetRear(),0,sizeof(OvPimple));

	SetNearClip(1.0f);
	SetFarClip(5000.0f);
	SetFOV((D3DX_PI*45.0f)/180.0f);
}
OvCamera::~OvCamera()
{

}

const OvPoint3&	OvCamera::GetWorldLookDirection()
{
	return m_pPimple->mLookDirection;
}
const OvPoint3&	OvCamera::GetWorldUpDirection()
{
	return m_pPimple->mUpDirection;
}
const OvPoint3&	OvCamera::GetWorldRightDirection()
{
	return m_pPimple->mRightDirection;
}
void			OvCamera::SetLookTarget(OvXObjectSPtr _pLookTarget)
{
	if(!_pLookTarget)
		return ;

	m_pPimple->mLookTarget = _pLookTarget;
}

OvXObjectSPtr		OvCamera::GetLookTarget()
{
	return m_pPimple->mLookTarget;
}

const OvMatrix&	OvCamera::GetViewMatrix()
{
	return m_pPimple->mViewMatrix;
}
const OvMatrix&	OvCamera::GetProjectMatrix()
{
	return m_pPimple->mProjectMatrix;
}

void			OvCamera::UpdateSubordinate(float _fElapse)
{
	const OvMatrix& kWorldMat = GetWorldTransform().BuildMatrix;

	m_pPimple->mUpDirection = OvPoint3(kWorldMat._31,kWorldMat._32,kWorldMat._33).Normalize();

	m_pPimple->mLookDirection = -OvPoint3(kWorldMat._21,kWorldMat._22,kWorldMat._23).Normalize();

	m_pPimple->mRightDirection = OvPoint3(kWorldMat._11,kWorldMat._12,kWorldMat._13).Normalize();

	UpdateProjection();
	UpdateView();
	UpdateLookAt();
	__super::UpdateSubordinate(_fElapse);
}

void					OvCamera::SetCameraType(OvCamera::eCameraType eType)
{
	m_pPimple->mType = eType;
}
OvCamera::eCameraType	OvCamera::GetCameraType()
{
	return m_pPimple->mType;
}
void			OvCamera::SetFOV(float fFOV)
{
	m_pPimple->mFOV = fFOV;
}
float			OvCamera::GetFOV()
{
	return m_pPimple->mFOV;
}
void			OvCamera::SetNearClip(float fDistance)
{
	m_pPimple->mNearClip = fDistance;
}
float			OvCamera::GetNearClip()
{
	return m_pPimple->mNearClip;
}
void			OvCamera::SetFarClip(float fDistance)
{
	m_pPimple->mFarClip = fDistance;
}
float			OvCamera::GetFarClip()
{
	return m_pPimple->mFarClip ;
}

void			OvCamera::UpdateProjection()
{
	D3DXMatrixPerspectiveFovLH((D3DXMATRIX*)&(m_pPimple->mProjectMatrix),GetFOV(),800.0f/600.0f,GetNearClip(),GetFarClip());
}

void			OvCamera::UpdateView()
{

	OvMatrix& krViewMat = m_pPimple->mViewMatrix;

	OvPoint3& krWorldPoint = (OvPoint3&)GetWorldTranslate();
	OvPoint3& krLookDir		= (OvPoint3&)GetWorldLookDirection();
	OvPoint3& krRightDir	= (OvPoint3&)GetWorldRightDirection();
	OvPoint3& krUpDir		= (OvPoint3&)GetWorldUpDirection();

	krViewMat = OvMatrix
		(krRightDir.x,krUpDir.x,krLookDir.x,0
		,krRightDir.y,krUpDir.y,krLookDir.y,0
		,krRightDir.z,krUpDir.z,krLookDir.z,0
		,-krRightDir.DotProduct(krWorldPoint),-krUpDir.DotProduct(krWorldPoint),-krLookDir.DotProduct(krWorldPoint),1);

}

void			OvCamera::UpdateLookAt()
{
	if (GetLookTarget())
	{
		/*OvXObjectSPtr	kLookTarget = GetLookTarget();
		OvPoint3	kLookDir = kLookTarget->GetTranslate() - GetTranslate();
		kLookDir = kLookDir.Normalize();
		OvPoint3	kRotAxis = OvPoint3CrossProduct(kLookDir,OvPoint3::AXIS_Y);
		float		kRotAngle = acosf(kLookDir.DotProduct(OvPoint3::AXIS_Y));
		OvQuaternion	kLookQuat;
		kLookQuat.MakeQuaternion(-kRotAxis,-kRotAngle);
		SetRotation(kLookQuat);*/
	}
}
