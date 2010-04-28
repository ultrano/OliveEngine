#include "OvCamera.h"
#include "OvTransform.h"
#include "OvRenderer.h"
#include <d3dx9.h>

OvRTTI_IMPL(OvCamera,OvXObject);

OvCamera::OvCamera()
{
	SetNearClip(1.0f);
	SetFarClip(5000.0f);
	SetFOV((D3DX_PI*45.0f)/180.0f);
}
OvCamera::~OvCamera()
{

}

const OvPoint3&	OvCamera::GetWorldLookDirection()
{
	return m_pt3LookDirection;
}
const OvPoint3&	OvCamera::GetWorldUpDirection()
{
	return m_pt3UpDirection;
}
const OvPoint3&	OvCamera::GetWorldRightDirection()
{
	return m_pt3RightDirection;
}
void			OvCamera::SetLookTarget(OvXObjectSPtr _pLookTarget)
{
	if(!_pLookTarget)
		return ;

	m_spLookTarget = _pLookTarget;
}

OvXObjectSPtr		OvCamera::GetLookTarget()
{
	return m_spLookTarget;
}

const OvMatrix&	OvCamera::GetViewMatrix()
{
	return m_mxViewMatrix;
}
const OvMatrix&	OvCamera::GetProjectMatrix()
{
	return m_mxProjectMatrix;
}

void			OvCamera::UpdateSubordinate(float _fElapse)
{
	const OvMatrix& kWorldMat = GetWorldTransform().BuildMatrix;

	m_pt3UpDirection = OvPoint3(kWorldMat._31,kWorldMat._32,kWorldMat._33).Normalize();

	m_pt3LookDirection = -OvPoint3(kWorldMat._21,kWorldMat._22,kWorldMat._23).Normalize();

	m_pt3RightDirection = OvPoint3(kWorldMat._11,kWorldMat._12,kWorldMat._13).Normalize();

	UpdateProjection();
	UpdateView();
	UpdateLookAt();
	__super::UpdateSubordinate(_fElapse);
}

void					OvCamera::SetCameraType(OvCamera::eCameraType eType)
{
	m_eCameraType = eType;
}
OvCamera::eCameraType	OvCamera::GetCameraType()
{
	return m_eCameraType;
}
void			OvCamera::SetFOV(float fFOV)
{
	m_fFOV = fFOV;
}
float			OvCamera::GetFOV()
{
	return m_fFOV;
}
void			OvCamera::SetNearClip(float fDistance)
{
	m_fNearClip = fDistance;
}
float			OvCamera::GetNearClip()
{
	return m_fNearClip;
}
void			OvCamera::SetFarClip(float fDistance)
{
	m_fFarClip = fDistance;
}
float			OvCamera::GetFarClip()
{
	return m_fFarClip ;
}

void			OvCamera::UpdateProjection()
{
	D3DXMatrixPerspectiveFovLH((D3DXMATRIX*)&(m_mxProjectMatrix),GetFOV(),800.0f/600.0f,GetNearClip(),GetFarClip());
}

void			OvCamera::UpdateView()
{

	OvMatrix& krViewMat = m_mxViewMatrix;

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
