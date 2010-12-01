#include "OvPoint2.h"
#include "OvUtility.h"

OvPoint2 OvPoint2::AXIS_X(1,0);
OvPoint2 OvPoint2::AXIS_Y(0,1);

OvPoint2 OvPoint2::Normalize()
{
	float kfLength = Length();
	return OvPoint2(x/kfLength,y/kfLength);
}
float	OvPoint2::DotProduct(const OvPoint2& _rPt)
{
	return float(x*_rPt.x + y*_rPt.y );
}
float	OvPoint2::Length()
{
	return  Length3D(x,y,0,0,0,0);
}
float	OvPoint2::Length(const OvPoint2& _rTargetPoint)
{
	return  Length3D(x,y,0,_rTargetPoint.x,_rTargetPoint.y,0);
}

OvPoint2 OvPoint2::operator +(const OvPoint2& _rPt) const
{
	return OvPoint2(x + _rPt.x,y + _rPt.y );
}
OvPoint2 OvPoint2::operator -(const OvPoint2& _rPt) const
{
	return OvPoint2(x - _rPt.x,y - _rPt.y );
}
OvPoint2 OvPoint2::operator -() const
{
	return OvPoint2(-x,-y);
}
OvPoint2 OvPoint2::operator *(float _fScalar) const
{
	return OvPoint2(x * _fScalar ,y * _fScalar );
}
OvPoint2	OvPoint2::operator /(float _fScalar) const
{
	return OvPoint2(x / _fScalar ,y / _fScalar );
}

OvPoint2& OvPoint2::operator +=(const OvPoint2& _rPt) 
{
	x += _rPt.x;
	y += _rPt.y;
	return *this;
}
OvPoint2& OvPoint2::operator -=(const OvPoint2& _rPt) 
{
	x -= _rPt.x;
	y -= _rPt.y;
	return *this;
}
OvBool	OvPoint2::operator ==(const OvPoint2& _rPt) const
{
	return ((x == _rPt.x)&&(y == _rPt.y));
}
OvBool	OvPoint2::operator !=(const OvPoint2& _rPt) const
{
	return ((x != _rPt.x)&&(y != _rPt.y));
}