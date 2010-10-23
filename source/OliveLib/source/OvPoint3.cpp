
#include "OvPoint3.h"
#include "OvUtility.h"
#include "OvMatrix.h"
#include "OvQuaternion.h"

OvPoint3 OvPoint3::AXIS_X(1,0,0);
OvPoint3 OvPoint3::AXIS_Y(0,1,0);
OvPoint3 OvPoint3::AXIS_Z(0,0,1);

OvPoint3 OvPoint3::Normalize()
{
	float kfLength = Length();
	return kfLength? OvPoint3(x/kfLength,y/kfLength,z/kfLength) : *this;
}
float	OvPoint3::DotProduct(const OvPoint3& _rPt)
{
	return float(x*_rPt.x + y*_rPt.y + z*_rPt.z);
}
float	OvPoint3::Length()
{
	return  Length3D(x,y,z,0,0,0);
}
float	OvPoint3::Length(const OvPoint3& _rTargetPoint)
{
	return OvPoint3Length(*this,_rTargetPoint);
}

OvPoint3 OvPoint3::operator +(const OvPoint3& _rPt) const
{
	return OvPoint3(x + _rPt.x,y + _rPt.y,z + _rPt.z);
}

OvPoint3 OvPoint3::operator -(const OvPoint3& _rPt) const
{
	return OvPoint3(x - _rPt.x,y - _rPt.y,z - _rPt.z);
}

OvPoint3 OvPoint3::operator -() const
{
	return OvPoint3(-x,-y,-z);
}

OvPoint3 OvPoint3::operator *(float _fScalar) const
{
	return OvPoint3(x * _fScalar ,y * _fScalar ,z * _fScalar );
}
OvPoint3	OvPoint3::operator /(float _fScalar) const
{
	return OvPoint3(x / _fScalar ,y / _fScalar ,z / _fScalar );
}
OvPoint3	OvPoint3::operator *(const OvMatrix mulMat) const
{
	/*
	D3DXVec3Transform((D3DXVECTOR4*)&outPut2,(D3DXVECTOR3*)this,(D3DXMATRIX*)&mulMat);
	return outPut;
	*/
	OvQuaternion outPut
	( ( x * mulMat._11 ) + ( y * mulMat._21 ) + ( z * mulMat._31 ) + ( 1 * mulMat._41 )
	, ( x * mulMat._12 ) + ( y * mulMat._22 ) + ( z * mulMat._32 ) + ( 1 * mulMat._42 )
	, ( x * mulMat._13 ) + ( y * mulMat._23 ) + ( z * mulMat._33 ) + ( 1 * mulMat._43 )
	, ( x * mulMat._14 ) + ( y * mulMat._24 ) + ( z * mulMat._34 ) + ( 1 * mulMat._44 )
	);
	float w = (outPut.w)? outPut.w : 1;
	return OvPoint3
		( outPut.x / w
		, outPut.y / w
		, outPut.z / w
		);
}

//OvPoint3 OvPoint3::operator *(const OvQuaternion& _rQuter) const
//{
//
//	return OvPoint3();
//}

OvPoint3& OvPoint3::operator +=(const OvPoint3& _rPt) 
{
	x += _rPt.x;
	y += _rPt.y;
	z += _rPt.z;
	return *this;
}
OvPoint3& OvPoint3::operator -=(const OvPoint3& _rPt) 
{
	x -= _rPt.x;
	y -= _rPt.y;
	z -= _rPt.z;
	return *this;
}
bool	OvPoint3::operator ==(const OvPoint3& _rPt) const
{
	return ((x == _rPt.x)&&(y == _rPt.y)&&(z == _rPt.z));
}

bool	OvPoint3::operator !=(const OvPoint3& _rPt) const
{
	return ((x != _rPt.x)&&(y != _rPt.y)&&(z != _rPt.z));
}
float	 OvPoint3DotProduct(const OvPoint3& _rPt0,const OvPoint3& _rPt1)
{
	return float(_rPt0.x*_rPt1.x + _rPt0.y*_rPt1.y + _rPt0.z*_rPt1.z);
}

OvPoint3 OvPoint3CrossProduct(const OvPoint3& _rPt0,const OvPoint3& _rPt1)
{
	return OvPoint3(_rPt0.y*_rPt1.z - _rPt0.z*_rPt1.y,_rPt0.z*_rPt1.x - _rPt0.x*_rPt1.z,_rPt0.x*_rPt1.y - _rPt0.y*_rPt1.x);
}

float	 OvPoint3Length(const OvPoint3& _rPt0,const OvPoint3& _rPt1)
{
	return Length3D(_rPt0.x,_rPt0.y,_rPt0.z,_rPt1.x,_rPt1.y,_rPt1.z);
}