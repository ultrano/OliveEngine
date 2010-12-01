#pragma once
#include "OvTypeDef.h"
#include "OvMemObject.h"
#include "OvPoint3.h"
class OvPlane	:	public OvMemObject
{
public:
	OvPlane():m_PlaneNormal(0,1,0),m_PlaneDistance(0){};
	OvPlane(const OvPoint3& _P0,const OvPoint3& _P1,const OvPoint3& _P2);
	OvPlane(const OvPoint3& _PlaneNormal,const OvPoint3& _P0);
	OvPlane(const OvPoint3& _PlaneNormal,OvFloat _PlaneDistance);
	virtual ~OvPlane(){};

	inline const OvPoint3& GetNormal();
	inline void		SetNormal(OvPoint3& _PlaneNormal);

	inline OvFloat	GetDistance();
	inline void		SetDistance(OvFloat	_PlaneDistance);

	inline void		SetPlane(const OvPoint3& _P0,const OvPoint3& _P1,const OvPoint3& _P2);
	inline void		SetPlane(const OvPoint3& _PlaneNormal,const OvPoint3& _P0);
	inline void		SetPlane(const OvPoint3& _PlaneNormal,OvFloat _PlaneDistance);

	OvInt			WhichSide(const OvPoint3& _SidePoint);
	enum
	{
		NEGATIVE_SIDE=-1,
		ON_THE_PLANE,
		POSITIVE_SIDE
	};

private:
	OvPoint3	m_PlaneNormal;
	OvFloat		m_PlaneDistance;
};
#include "OvPlane.inl"
