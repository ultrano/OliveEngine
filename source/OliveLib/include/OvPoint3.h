#pragma once
#include "OvTypeDef.h"

//// 나중에 만들어 주자;
//typedef	D3DXVECTOR3	OvPoint3;
class OvQuaternion;
class OvMatrix;
class OvPoint3
{
public:
	static OvPoint3	AXIS_X;
	static OvPoint3	AXIS_Y;
	static OvPoint3	AXIS_Z;
public :
	OvPoint3():x(0),y(0),z(0){};
	OvPoint3(float _fX,float _fY,float _fZ):x(_fX),y(_fY),z(_fZ){};

	OvPoint3	Normalize();
	float		DotProduct(const OvPoint3& _rPt);
	float		Length();
	float		Length(const OvPoint3& _rTargetPoint);

	OvPoint3	operator +(const OvPoint3& _rPt) const;
	OvPoint3	operator -(const OvPoint3& _rPt) const;
	OvPoint3	operator -() const;
	OvPoint3	operator *(float _fScalar) const;
	OvPoint3	operator /(float _fScalar) const;
	OvPoint3	operator *(const OvMatrix mulMat) const;
	//OvPoint3 operator *(const OvQuaternion& _rQuter) const;

	OvPoint3&	operator +=(const OvPoint3& _rPt) ;
	OvPoint3&	operator -=(const OvPoint3& _rPt) ;
	OvBool		operator ==(const OvPoint3& _rPt) const;
	OvBool		operator !=(const OvPoint3& _rPt) const;

	float x,y,z;
};



float	 OvPoint3DotProduct(const OvPoint3& _rPt0,const OvPoint3& _rPt1);
OvPoint3 OvPoint3CrossProduct(const OvPoint3& _rPt0,const OvPoint3& _rPt1);
float	 OvPoint3Length(const OvPoint3& _rPt0,const OvPoint3& _rPt1);