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

	virtual void	UpdateSubordinate( OvFloat _fElapse ) override;

	void			SetFOV(OvFloat fFOV);
	OvFloat			GetFOV();

	void			SetNearClip(OvFloat fDistance);
	OvFloat			GetNearClip();
	void			SetFarClip(OvFloat fDistance);
	OvFloat			GetFarClip();

	void			SetAspect( OvFloat aspect );
	OvFloat			GetAspect();
private:
	void			UpdateProjection();
	void			UpdateLight();
private:

	OvMatrix	m_light_matrix;
	OvMatrix	m_project_matrix;

	OvFloat		m_fov;
	OvFloat		m_near_clip;
	OvFloat		m_far_clip;
	OvFloat		m_aspect;
};