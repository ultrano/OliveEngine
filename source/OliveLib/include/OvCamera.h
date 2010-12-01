#pragma once
#include "OvXNode.h"
#include "OvTransform.h"
#include "OvObjectFactory.h"
//! Predeclare Class
OvREF_POINTER(OvXObject);
//
OvREF_POINTER(OvCamera);
class OvCamera : public OvXNode
{
	OvRTTI_DECL(OvCamera);
	OvPROPERTY_BAG_DECL(OvCamera);
	OvFACTORY_OBJECT_DECL(OvCamera);
private:
	OvCamera();
public:

	enum	eCameraType
	{
		eCameraType_None,
		eCameraType_Free,
		eCameraType_Target,
	};

	~OvCamera();


	OvPoint3	GetLocalLookDirection();
	OvPoint3	GetLocalUpDirection();
	OvPoint3	GetLocalRightDirection();

	OvPoint3	GetWorldLookDirection();
	OvPoint3	GetWorldUpDirection();
	OvPoint3	GetWorldRightDirection();

	void			SetLookTarget(OvXObjectSPtr _pLookTarget);
	OvXObjectSPtr	GetLookTarget();

	const OvMatrix&	GetViewMatrix();
	const OvMatrix&	GetProjectMatrix();

	virtual void	UpdateSubordinate( float _fElapse ) override;

	void			SetCameraType(eCameraType eType);
	eCameraType		GetCameraType();

	void			SetFOV(float fFOV);
	float			GetFOV();

	void			SetNearClip(float fDistance);
	float			GetNearClip();
	void			SetFarClip(float fDistance);
	float			GetFarClip();

	void			SetAspect( float aspect );
	float			GetAspect();

protected:

	void			UpdateProjection();
	void			UpdateView();
	void			UpdateLookAt();

private:

	OvMatrix	m_mxViewMatrix;
	OvMatrix	m_mxProjectMatrix;

	OvXObjectSPtr m_spLookTarget;

	eCameraType	m_eCameraType;

	float		m_fFOV;
	float		m_fNearClip;
	float		m_fFarClip;
	float		m_aspect;

};