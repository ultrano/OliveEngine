#include "OvCamera.h"
#include "OvTransform.h"
#include "OvRenderer.h"
#include "OvRegisterableProperties.h"
#include <d3dx9.h>

OvRTTI_IMPL(OvCamera);
OvPROPERTY_BAG_BEGIN(OvCamera);
	OvPROPERTY_BAG_REGISTER( OvProp_object_smart_pointer, m_spLookTarget )
	OvPROPERTY_BAG_REGISTER( OvProp_integer, m_eCameraType )
	OvPROPERTY_BAG_REGISTER( OvProp_float, m_fFOV )
	OvPROPERTY_BAG_REGISTER( OvProp_float, m_fNearClip )
	OvPROPERTY_BAG_REGISTER( OvProp_float, m_fFarClip )
	OvPROPERTY_BAG_REGISTER( OvProp_float, m_aspect )
OvPROPERTY_BAG_END(OvCamera);

OvCamera::OvCamera()
{
	SetNearClip(1.0f);
	SetFarClip(5000.0f);
	SetFOV( ( D3DX_PI * 45.0f ) / 180.0f );
	SetAspect( 800.0f / 600.0f );
}
OvCamera::~OvCamera()
{

}

OvPoint3	OvCamera::GetWorldLookDirection()
{
	return -OvPoint3(GetWorldMatrix()._21,GetWorldMatrix()._22,GetWorldMatrix()._23).Normalize();;
}
OvPoint3	OvCamera::GetWorldUpDirection()
{
	return OvPoint3(GetWorldMatrix()._31,GetWorldMatrix()._32,GetWorldMatrix()._33).Normalize();
}
OvPoint3	OvCamera::GetWorldRightDirection()
{
	return OvPoint3(GetWorldMatrix()._11,GetWorldMatrix()._12,GetWorldMatrix()._13).Normalize();	
}


OvPoint3	OvCamera::GetLocalLookDirection()
{
	return -OvPoint3(GetLocalMatrix()._21,GetLocalMatrix()._22,GetLocalMatrix()._23).Normalize();
}
OvPoint3	OvCamera::GetLocalUpDirection()
{
	return OvPoint3(GetLocalMatrix()._31,GetLocalMatrix()._32,GetLocalMatrix()._33).Normalize();
}
OvPoint3	OvCamera::GetLocalRightDirection()
{
	return OvPoint3(GetLocalMatrix()._11,GetLocalMatrix()._12,GetLocalMatrix()._13).Normalize();
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

void			OvCamera::SetAspect( float aspect )
{
	m_aspect = aspect;
}
float			OvCamera::GetAspect()
{
	return m_aspect;
}

void			OvCamera::UpdateProjection()
{
	D3DXMatrixPerspectiveFovLH
		( (D3DXMATRIX*)&(m_mxProjectMatrix)
		, GetFOV()
		, GetAspect()
		, GetNearClip()
		, GetFarClip() );
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
