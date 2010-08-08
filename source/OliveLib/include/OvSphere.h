#pragma once

#include "OvMemObject.h"
#include "OvPoint3.h"
class OvSphere : public OvMemObject
{
public:
	OvSphere();
	OvSphere(const OvPoint3& _pt3Center,float _fRadius);
	OvSphere(const OvSphere& _rCopy);

	void		SetCenter(const OvPoint3& _rCenter);
	void		SetRadius(float _fRadius);
	const OvPoint3&	GetCenter()const;
	float		GetRadius()const;

protected:
private:
	OvPoint3	m_pt3CenterPoint;
	float		m_fRadius;
};