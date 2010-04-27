#pragma once
#include "OvXObject.h"
#include "OvTransform.h"
//! Predeclare Class
OvREF_POINTER(OvXObject);
//
OvREF_POINTER(OvCamera);
class OvCamera : public OvXObject
{
	OvRTTI_DECL(OvCamera);

public:

	enum	eCameraType
	{
		eCameraType_None,
		eCameraType_Free,
		eCameraType_Target,
	};

	OvCamera();
	~OvCamera();
	
	const OvPoint3&	GetWorldLookDirection();
	const OvPoint3&	GetWorldUpDirection();
	const OvPoint3&	GetWorldRightDirection();

	void			SetLookTarget(OvXObjectSPtr _pLookTarget);
	OvXObjectSPtr	GetLookTarget();

	const OvMatrix&	GetViewMatrix();
	const OvMatrix&	GetProjectMatrix();

	virtual void	UpdateSubordinate(float _fElapse);

	void			SetCameraType(eCameraType eType);
	eCameraType		GetCameraType();

	void			SetFOV(float fFOV);
	float			GetFOV();

	void			SetNearClip(float fDistance);
	float			GetNearClip();
	void			SetFarClip(float fDistance);
	float			GetFarClip();


protected:

	void			UpdateProjection();
	void			UpdateView();
	void			UpdateLookAt();

private:
	struct OvPimple;
	OvAutoPtr< OvPimple> m_pPimple;
};