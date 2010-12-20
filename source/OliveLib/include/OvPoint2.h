#pragma once
#include "OvTypeDef.h"

class OvPoint2
{
public:
	static OvPoint2	AXIS_X;
	static OvPoint2	AXIS_Y;
public:
	OvPoint2():x(0),y(0){};
	OvPoint2(OvFloat fX,OvFloat fY):x(fX),y(fY){};
	OvPoint2	Normalize();
	OvFloat		DotProduct(const OvPoint2& _rPt);
	OvFloat		Length();
	OvFloat		Length(const OvPoint2& _rTargetPoint);

	OvPoint2	operator +(const OvPoint2& _rPt) const;
	OvPoint2	operator -(const OvPoint2& _rPt) const;
	OvPoint2	operator -() const;
	OvPoint2	operator *(OvFloat _fScalar) const;
	OvPoint2	operator /(OvFloat _fScalar) const;

	OvPoint2&	operator +=(const OvPoint2& _rPt) ;
	OvPoint2&	operator -=(const OvPoint2& _rPt) ;
	OvBool		operator ==(const OvPoint2& _rPt) const;
	OvBool		operator !=(const OvPoint2& _rPt) const;
public:
	OvFloat x,y;
};