#pragma once
#pragma warning( disable : 4521 )
#include "OvTypeDef.h"

class OvPoint3;

class OvQuaternion
{
public:
	OvQuaternion() ;
	OvQuaternion(OvQuaternion& ) ;
	OvQuaternion(const OvQuaternion& );
	OvQuaternion( OvFloat fX, OvFloat fY, OvFloat fZ, OvFloat fW );

	operator OvFloat* ();
	operator const OvFloat* () const;

	OvQuaternion& operator += ( const OvQuaternion& );
	OvQuaternion& operator -= ( const OvQuaternion& );
	OvQuaternion& operator *= ( const OvQuaternion& );
	OvQuaternion& operator *= ( OvFloat );
	OvQuaternion& operator /= ( OvFloat );

	OvQuaternion  operator + () const;
	OvQuaternion  operator - () const;

	OvQuaternion operator + ( const OvQuaternion& ) const;
	OvQuaternion operator - ( const OvQuaternion& ) const;
	OvQuaternion operator * ( const OvQuaternion& ) const;
	OvQuaternion operator * ( OvFloat ) const;
	OvQuaternion operator / ( OvFloat ) const;

	friend OvQuaternion operator * (OvFloat, const OvQuaternion& );

	OvBool operator == ( const OvQuaternion& ) const;
	OvBool operator != ( const OvQuaternion& ) const;

	//!


	OvQuaternion&		Identity();
	OvQuaternion&		MakeQuaternion(OvFloat _fAxisX,OvFloat _fAxisY,OvFloat _fAxisZ,OvFloat _fAngleRadian);
	OvQuaternion&		MakeQuaternion(const OvPoint3& _rAxis,OvFloat _fAngleRadian);
	OvQuaternion		Inverse();

public:
	OvFloat x,y,z,w;
};

OvQuaternion	OvQuaternionSphericalInterpolate(OvFloat fRate,const OvQuaternion& crScr,const OvQuaternion& crDest );
OvQuaternion	OvEulerToQuaternion(OvFloat fX_Rotation,OvFloat fY_Rotation,OvFloat fZ_Rotation);