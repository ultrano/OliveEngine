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
	OvFACTORY_OBJECT_DECL(OvCamera);
public:

	enum	eCameraType
	{
		eCameraType_None,
		eCameraType_Free,
		eCameraType_Target,
	};

	OvCamera();
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

	virtual void	UpdateSubordinate( OvFloat _fElapse ) override;

	void			SetCameraType(eCameraType eType);
	eCameraType		GetCameraType();

	void			SetFOV(OvFloat fFOV);
	OvFloat			GetFOV();

	void			SetNearClip(OvFloat fDistance);
	OvFloat			GetNearClip();
	void			SetFarClip(OvFloat fDistance);
	OvFloat			GetFarClip();

	void			SetAspect( OvFloat aspect );
	OvFloat			GetAspect();

public:

	virtual void Serialize( OvObjectOutputStream & output ) override;
	virtual void Deserialize( OvObjectInputStream & input ) override;

protected:

	void			UpdateProjection();
	void			UpdateView();
	void			UpdateLookAt();

private:

	OvMatrix	m_mxViewMatrix;
	OvMatrix	m_mxProjectMatrix;

	OvXObjectSPtr m_spLookTarget;

	eCameraType	m_eCameraType;

	OvFloat		m_fFOV;
	OvFloat		m_fNearClip;
	OvFloat		m_fFarClip;
	OvFloat		m_aspect;

};