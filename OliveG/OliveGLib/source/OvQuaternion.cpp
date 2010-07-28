#include "OvQuaternion.h"
#include "OvPoint3.h"
#include <d3dx9.h>

OvQuaternion::OvQuaternion()
{
	D3DXQuaternionIdentity((D3DXQUATERNION*)this);
}

OvQuaternion::OvQuaternion(OvQuaternion& _rQuat) 
{
	memcpy((void*)this,(void*)&_rQuat,sizeof(OvQuaternion));
}
OvQuaternion::OvQuaternion(const OvQuaternion& _rQuat)
{
	memcpy((void*)this,(void*)&_rQuat,sizeof(OvQuaternion));
}
OvQuaternion::OvQuaternion(  float fX, float fY, float fZ, float fW )
:x(fX)
,y(fY)
,z(fZ)
,w(fW)
{
}

OvQuaternion::operator float* ()
{
	return (float*)this;
}
OvQuaternion::operator const float* () const
{
	return (const float*)this;
}

OvQuaternion& OvQuaternion::operator += ( const OvQuaternion& _rQuat)
{
	*this = *this + _rQuat;
	return *this;
}
OvQuaternion& OvQuaternion::operator -= ( const OvQuaternion& _rQuat)
{
	*this = *this - _rQuat;
	return *this;
}
OvQuaternion& OvQuaternion::operator *= ( const OvQuaternion& _rQuat)
{
	*this = *this * _rQuat;
	return *this;
}
OvQuaternion& OvQuaternion::operator *= ( float _fValue)
{
	x *= _fValue;
	y *= _fValue;
	z *= _fValue;
	w *= _fValue;
	return *this;
}
OvQuaternion& OvQuaternion::operator /= ( float _fValue)
{
	x /= _fValue;
	y /= _fValue;
	z /= _fValue;
	w /= _fValue;
	return *this;
}

//

OvQuaternion  OvQuaternion::operator + () const
{
	return *this;
}
OvQuaternion  OvQuaternion::operator - () const
{
	return -1*(*this);
}

//

OvQuaternion OvQuaternion::operator + ( const OvQuaternion& _rQuat) const
{
	return OvQuaternion(x + _rQuat.x,y + _rQuat.y,z + _rQuat.z,w + _rQuat.w);
}
OvQuaternion OvQuaternion::operator - ( const OvQuaternion& _rQuat) const
{
	return OvQuaternion(x - _rQuat.x,y - _rQuat.y,z - _rQuat.z,w - _rQuat.w);
}
OvQuaternion OvQuaternion::operator * ( const OvQuaternion& _rQuat) const
{
	OvQuaternion kOutput;
	D3DXQuaternionMultiply((D3DXQUATERNION*)&kOutput,(D3DXQUATERNION*)&_rQuat,(D3DXQUATERNION*)this);
	return kOutput;
}
OvQuaternion OvQuaternion::operator * ( float _fValue) const
{
	return OvQuaternion(x * _fValue,y * _fValue,z * _fValue,w * _fValue);
}
OvQuaternion OvQuaternion::operator / ( float _fValue) const
{
	return OvQuaternion(x / _fValue,y / _fValue,z / _fValue,w / _fValue);
}


OvQuaternion operator * (float _fValue, const OvQuaternion& _rQuat)
{
	return OvQuaternion(_rQuat.x * _fValue,_rQuat.y * _fValue,_rQuat.z * _fValue,_rQuat.w * _fValue);
}


bool OvQuaternion::operator == ( const OvQuaternion& _rQuat) const
{
	return ! (memcmp((void*)this,(void*)&_rQuat,sizeof(OvQuaternion)));
}
bool OvQuaternion::operator != ( const OvQuaternion& _rQuat) const
{
	return !(*this == _rQuat);
}


OvQuaternion&		OvQuaternion::Identity()
{
	D3DXQuaternionIdentity((D3DXQUATERNION*)this);
	return *this;
}

OvQuaternion&		OvQuaternion::MakeQuaternion(float _fAxisX,float _fAxisY,float _fAxisZ,float _fAngleRadian)
{
	MakeQuaternion(OvPoint3(_fAxisX,_fAxisY,_fAxisZ),_fAngleRadian);
	return *this;
}

OvQuaternion&		OvQuaternion::MakeQuaternion(const OvPoint3& _rAxis,float _fAngleRadian)
{
	OvPoint3 kNormAxis = ((OvPoint3&)_rAxis).Normalize();
	kNormAxis = kNormAxis * sinf(_fAngleRadian/2.0f);
	x = kNormAxis.x;
	y = kNormAxis.y;
	z = kNormAxis.z;
	w = cosf(_fAngleRadian/2.0f);
	return *this;
}
OvQuaternion		OvQuaternion::Inverse()
{
	OvQuaternion kInverse;
	D3DXQuaternionInverse((D3DXQUATERNION*)&kInverse,(D3DXQUATERNION*)this);
	return kInverse;
}
OvQuaternion	OvQuaternionSphericalInterpolate(float fRate,const OvQuaternion& crScr,const OvQuaternion& crDest)
{
	OvQuaternion	kResult;
	D3DXQuaternionSlerp((D3DXQUATERNION*)&kResult,(D3DXQUATERNION*)&crScr,(D3DXQUATERNION*)&crDest,fRate);
	return kResult;
}
OvQuaternion	OvEulerToQuaternion(float fX_Rotation,float fY_Rotation,float fZ_Rotation)
{
	OvQuaternion	kQuat;
		
	kQuat.w		=	cosf(fX_Rotation/2.0f)*cosf(fY_Rotation/2.0f)*cosf(fZ_Rotation/2.0f) - sinf(fX_Rotation/2.0f)*sinf(fY_Rotation/2.0f)*sinf(fZ_Rotation/2.0f);
	kQuat.x		=	-sinf(fX_Rotation/2.0f)*cosf(fY_Rotation/2.0f)*cosf(fZ_Rotation/2.0f) - cosf(fX_Rotation/2.0f)*sinf(fY_Rotation/2.0f)*sinf(fZ_Rotation/2.0f);
	kQuat.y		=	-cosf(fX_Rotation/2.0f)*sinf(fY_Rotation/2.0f)*cosf(fZ_Rotation/2.0f) + sinf(fX_Rotation/2.0f)*cosf(fY_Rotation/2.0f)*sinf(fZ_Rotation/2.0f);
	kQuat.z		=	-cosf(fX_Rotation/2.0f)*cosf(fY_Rotation/2.0f)*sinf(fZ_Rotation/2.0f) - sinf(fX_Rotation/2.0f)*sinf(fY_Rotation/2.0f)*cosf(fZ_Rotation/2.0f);

	return kQuat;

}