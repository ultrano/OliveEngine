#include "OvPlane.h"

inline const OvPoint3& OvPlane::GetNormal()
{
	return m_PlaneNormal;
};

inline void		OvPlane::SetNormal(OvPoint3& _PlaneNormal)
{
	m_PlaneNormal	=	_PlaneNormal;
	m_PlaneNormal	=	m_PlaneNormal.Normalize();
};

inline OvFloat	OvPlane::GetDistance()
{
	return m_PlaneDistance;
};
inline void		OvPlane::SetDistance(OvFloat	_PlaneDistance)
{
	m_PlaneDistance		=	_PlaneDistance;
};

inline void		OvPlane::SetPlane(const OvPoint3& _P0,const OvPoint3& _P1,const OvPoint3& _P2)
{
	OvPoint3 kDir0	=	_P1 - _P0;
	OvPoint3 kDir1	=	_P2 - _P0;
	m_PlaneNormal = OvPoint3CrossProduct(kDir0,kDir1);
	m_PlaneNormal = m_PlaneNormal.Normalize();
	m_PlaneDistance	=	m_PlaneNormal.DotProduct(_P0);
};

inline void		OvPlane::SetPlane(const OvPoint3& _PlaneNormal,const OvPoint3& _P0)
{
	m_PlaneNormal	=	_PlaneNormal;
	m_PlaneNormal = m_PlaneNormal.Normalize();
	m_PlaneDistance	=	m_PlaneNormal.DotProduct(_P0);
};

inline void		OvPlane::SetPlane(const OvPoint3& _PlaneNormal,OvFloat _PlaneDistance)
{
	m_PlaneDistance		=	_PlaneDistance;
	m_PlaneNormal	=	_PlaneNormal;
	m_PlaneNormal = m_PlaneNormal.Normalize();
};