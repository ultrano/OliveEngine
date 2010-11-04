#pragma once
#pragma warning( disable : 4521 )

class OvPoint3;

class OvQuaternion
{
public:
	OvQuaternion() ;
	OvQuaternion(OvQuaternion& ) ;
	OvQuaternion(const OvQuaternion& );
	OvQuaternion( float fX, float fY, float fZ, float fW );

	operator float* ();
	operator const float* () const;

	OvQuaternion& operator += ( const OvQuaternion& );
	OvQuaternion& operator -= ( const OvQuaternion& );
	OvQuaternion& operator *= ( const OvQuaternion& );
	OvQuaternion& operator *= ( float );
	OvQuaternion& operator /= ( float );

	OvQuaternion  operator + () const;
	OvQuaternion  operator - () const;

	OvQuaternion operator + ( const OvQuaternion& ) const;
	OvQuaternion operator - ( const OvQuaternion& ) const;
	OvQuaternion operator * ( const OvQuaternion& ) const;
	OvQuaternion operator * ( float ) const;
	OvQuaternion operator / ( float ) const;

	friend OvQuaternion operator * (float, const OvQuaternion& );

	bool operator == ( const OvQuaternion& ) const;
	bool operator != ( const OvQuaternion& ) const;

	//!


	OvQuaternion&		Identity();
	OvQuaternion&		MakeQuaternion(float _fAxisX,float _fAxisY,float _fAxisZ,float _fAngleRadian);
	OvQuaternion&		MakeQuaternion(const OvPoint3& _rAxis,float _fAngleRadian);
	OvQuaternion		Inverse();

public:
	float x,y,z,w;
};

OvQuaternion	OvQuaternionSphericalInterpolate(float fRate,const OvQuaternion& crScr,const OvQuaternion& crDest );
OvQuaternion	OvEulerToQuaternion(float fX_Rotation,float fY_Rotation,float fZ_Rotation);