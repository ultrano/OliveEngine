#pragma once
#include "OvLight.h"

class OvSpotLight : public OvLight
{
	OvRTTI_DECL(OvSpotLight);
public:
	OvPoint3	GetLocalLookDirection();
	OvPoint3	GetLocalUpDirection();
	OvPoint3	GetLocalRightDirection();

	OvPoint3	GetWorldLookDirection();
	OvPoint3	GetWorldUpDirection();
	OvPoint3	GetWorldRightDirection();

	const OvMatrix&	GetLightMatrix();
	const OvMatrix&	GetProjectMatrix();

	virtual void	UpdateSubordinate( float _fElapse ) override;

	void			SetFOV(float fFOV);
	float			GetFOV();

	void			SetNearClip(float fDistance);
	float			GetNearClip();
	void			SetFarClip(float fDistance);
	float			GetFarClip();

	void			SetAspect( float aspect );
	float			GetAspect();
private:
	void			UpdateProjection();
	void			UpdateLight();
private:

	OvMatrix	m_light_matrix;
	OvMatrix	m_project_matrix;

	float		m_fov;
	float		m_near_clip;
	float		m_far_clip;
	float		m_aspect;
};