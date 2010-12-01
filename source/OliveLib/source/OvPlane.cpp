#include "OvPlane.h"


OvPlane::OvPlane(const OvPoint3& _P0,const OvPoint3& _P1,const OvPoint3& _P2)
{
	OvPoint3 kDir0	=	_P1 - _P0;
	OvPoint3 kDir1	=	_P2 - _P0;
	m_PlaneNormal = OvPoint3CrossProduct(kDir0,kDir1);
		m_PlaneNormal = m_PlaneNormal.Normalize();
	m_PlaneDistance	=	m_PlaneNormal.DotProduct(_P0);
};

OvPlane::OvPlane(const OvPoint3& _PlaneNormal,const OvPoint3& _P0):m_PlaneNormal(_PlaneNormal)
{
	m_PlaneNormal = m_PlaneNormal.Normalize();
	m_PlaneDistance	=	m_PlaneNormal.DotProduct(_P0);
};

OvPlane::OvPlane(const OvPoint3& _PlaneNormal,OvFloat _PlaneDistance):m_PlaneNormal(_PlaneNormal),m_PlaneDistance(_PlaneDistance)
{
	m_PlaneNormal = m_PlaneNormal.Normalize();
};

OvInt			OvPlane::WhichSide(const OvPoint3& _SidePoint)
{
	OvFloat	kWhichSide	=	m_PlaneNormal.DotProduct(_SidePoint);

	kWhichSide	=	kWhichSide - m_PlaneDistance;

	if(kWhichSide<0)
		return NEGATIVE_SIDE;
	else if(kWhichSide>0)
		return POSITIVE_SIDE;

	return ON_THE_PLANE;
};