#include "OvSphere.h"

OvSphere::OvSphere():
m_pt3CenterPoint(0,0,0),
m_fRadius(0)
{

}
OvSphere::OvSphere(const OvPoint3& _pt3Center,float _fRadius):
m_pt3CenterPoint(_pt3Center),
m_fRadius(_fRadius)
{

}
OvSphere::OvSphere(const OvSphere& _rCopy)
{

}

void		OvSphere::SetCenter(const OvPoint3& _rCenter)
{
	m_pt3CenterPoint = _rCenter;
}
void		OvSphere::SetRadius(float _fRadius)
{
	m_fRadius = _fRadius;
}

const OvPoint3&	OvSphere::GetCenter()const
{
	return m_pt3CenterPoint;
}
float		OvSphere::GetRadius()const
{
	return m_fRadius;
}
