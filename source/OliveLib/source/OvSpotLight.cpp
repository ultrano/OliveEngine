#include "OvSpotLight.h"
#include <d3dx9.h>
OvRTTI_IMPL(OvSpotLight);

OvPoint3	OvSpotLight::GetWorldLookDirection()
{
	return -OvPoint3(GetWorldMatrix()._21,GetWorldMatrix()._22,GetWorldMatrix()._23).Normalize();;
}
OvPoint3	OvSpotLight::GetWorldUpDirection()
{
	return OvPoint3(GetWorldMatrix()._31,GetWorldMatrix()._32,GetWorldMatrix()._33).Normalize();
}
OvPoint3	OvSpotLight::GetWorldRightDirection()
{
	return OvPoint3(GetWorldMatrix()._11,GetWorldMatrix()._12,GetWorldMatrix()._13).Normalize();	
}

OvPoint3	OvSpotLight::GetLocalLookDirection()
{
	return -OvPoint3(GetLocalMatrix()._21,GetLocalMatrix()._22,GetLocalMatrix()._23).Normalize();
}
OvPoint3	OvSpotLight::GetLocalUpDirection()
{
	return OvPoint3(GetLocalMatrix()._31,GetLocalMatrix()._32,GetLocalMatrix()._33).Normalize();
}
OvPoint3	OvSpotLight::GetLocalRightDirection()
{
	return OvPoint3(GetLocalMatrix()._11,GetLocalMatrix()._12,GetLocalMatrix()._13).Normalize();
}

const OvMatrix&	OvSpotLight::GetLightMatrix()
{
	return m_light_matrix;
}
const OvMatrix&	OvSpotLight::GetProjectMatrix()
{
	return m_project_matrix;
}

void			OvSpotLight::UpdateSubordinate(float _fElapse)
{
	UpdateProjection();
	UpdateLight();

	__super::UpdateSubordinate(_fElapse);
}

void			OvSpotLight::SetFOV(float fFOV)
{
	m_fov = fFOV;
}
float			OvSpotLight::GetFOV()
{
	return m_fov;
}
void			OvSpotLight::SetNearClip(float fDistance)
{
	m_near_clip = fDistance;
}
float			OvSpotLight::GetNearClip()
{
	return m_near_clip;
}
void			OvSpotLight::SetFarClip(float fDistance)
{
	m_far_clip = fDistance;
}
float			OvSpotLight::GetFarClip()
{
	return m_far_clip ;
}

void			OvSpotLight::SetAspect( float aspect )
{
	m_aspect = aspect;
}
float			OvSpotLight::GetAspect()
{
	return m_aspect;
}

void			OvSpotLight::UpdateProjection()
{
	D3DXMatrixPerspectiveFovLH
		( (D3DXMATRIX*)&(m_project_matrix)
		, GetFOV()
		, GetAspect()
		, GetNearClip()
		, GetFarClip() );
}

void			OvSpotLight::UpdateLight()
{
	MakeViewMatrix( GetWorldLookDirection(), GetWorldUpDirection(), GetWorldTranslate(), m_light_matrix );
}
