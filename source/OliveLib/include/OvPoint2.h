#pragma once

class OvPoint2
{
public:
	static OvPoint2	AXIS_X;
	static OvPoint2	AXIS_Y;
public:
	OvPoint2():x(0),y(0){};
	OvPoint2(float fX,float fY):x(fX),y(fY){};
	OvPoint2	Normalize();
	float		DotProduct(const OvPoint2& _rPt);
	float		Length();
	float		Length(const OvPoint2& _rTargetPoint);

	OvPoint2	operator +(const OvPoint2& _rPt) const;
	OvPoint2	operator -(const OvPoint2& _rPt) const;
	OvPoint2	operator -() const;
	OvPoint2	operator *(float _fScalar) const;
	OvPoint2	operator /(float _fScalar) const;

	OvPoint2&	operator +=(const OvPoint2& _rPt) ;
	OvPoint2&	operator -=(const OvPoint2& _rPt) ;
	bool		operator ==(const OvPoint2& _rPt) const;
	bool		operator !=(const OvPoint2& _rPt) const;
public:
	float x,y;
};