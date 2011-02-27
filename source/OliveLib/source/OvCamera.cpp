#include "OvCamera.h"
#include "OvTransform.h"
#include "OvRenderer.h"
#include <d3dx9.h>

OvRTTI_IMPL(OvCamera);
OvFACTORY_OBJECT_IMPL(OvCamera);

OvCamera::OvCamera()
{
	SetNearClip(1.0f);
	SetFarClip(10000.0f);
	SetFOV( ( D3DX_PI * 45.0f ) / 180.0f );
	SetAspect( (OvFloat)WindowWidth / (OvFloat)WindowHeight );
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

void			OvCamera::UpdateSubordinate(OvFloat _fElapse)
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
void			OvCamera::SetFOV(OvFloat fFOV)
{
	m_fFOV = fFOV;
}
OvFloat			OvCamera::GetFOV()
{
	return m_fFOV;
}
void			OvCamera::SetNearClip(OvFloat fDistance)
{
	m_fNearClip = fDistance;
}
OvFloat			OvCamera::GetNearClip()
{
	return m_fNearClip;
}
void			OvCamera::SetFarClip(OvFloat fDistance)
{
	m_fFarClip = fDistance;
}
OvFloat			OvCamera::GetFarClip()
{
	return m_fFarClip ;
}

void			OvCamera::SetAspect( OvFloat aspect )
{
	m_aspect = aspect;
}
OvFloat			OvCamera::GetAspect()
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
	MakeViewMatrix( GetWorldLookDirection(), GetWorldUpDirection(), GetWorldTranslate(), m_mxViewMatrix );
}

void			OvCamera::UpdateLookAt()
{
	if (GetLookTarget())
	{
		/*OvXObjectSPtr	kLookTarget = GetLookTarget();
		OvPoint3	kLookDir = kLookTarget->GetTranslate() - GetTranslate();
		kLookDir = kLookDir.Normalize();
		OvPoint3	kRotAxis = OvPoint3CrossProduct(kLookDir,OvPoint3::AXIS_Y);
		OvFloat		kRotAngle = acosf(kLookDir.DotProduct(OvPoint3::AXIS_Y));
		OvQuaternion	kLookQuat;
		kLookQuat.MakeQuaternion(-kRotAxis,-kRotAngle);
		SetRotation(kLookQuat);*/
	}
}

void OvCamera::Serialize( OvObjectOutputStream & output )
{
	__super::Serialize( output );

	output.Write( m_mxViewMatrix );
	output.Write( m_mxProjectMatrix );
	output.WriteObject( m_spLookTarget );
	output.Write( m_eCameraType );
	output.Write( m_fFOV );
	output.Write( m_fNearClip );
	output.Write( m_fFarClip );
	output.Write( m_aspect );

}

void OvCamera::Deserialize( OvObjectInputStream & input )
{
	__super::Deserialize( input );

	input.Read( m_mxViewMatrix );
	input.Read( m_mxProjectMatrix );
	m_spLookTarget = OvCastTo<OvXObject>( input.ReadObject() );
	input.Read( m_eCameraType );
	input.Read( m_fFOV );
	input.Read( m_fNearClip );
	input.Read( m_fFarClip );
	input.Read( m_aspect );

}
