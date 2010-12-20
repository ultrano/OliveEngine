#pragma once
#include "OvTypeDef.h"
#include "OvPoint3.h"
#include "OvQuaternion.h"


//typedef	D3DXMATRIXA16	OvMatrix;
class OvMatrix
{
public:

	OvMatrix();
	OvMatrix(const OvMatrix& );
	OvMatrix
		(OvFloat k11,OvFloat k12,OvFloat k13,OvFloat k14
		,OvFloat k21,OvFloat k22,OvFloat k23,OvFloat k24
		,OvFloat k31,OvFloat k32,OvFloat k33,OvFloat k34
		,OvFloat k41,OvFloat k42,OvFloat k43,OvFloat k44);

	OvMatrix	operator * (const OvMatrix&);
	OvMatrix	operator * (OvFloat );

	friend OvMatrix operator * (OvFloat, const OvMatrix& );
	friend OvMatrix operator * (const OvMatrix&, const OvMatrix& );

	OvMatrix&	Identity();

	OvMatrix&	Scale(OvFloat _fTotalScale);
	OvMatrix&	Scale(OvFloat x,OvFloat y,OvFloat z);
	OvMatrix&	Scale(const OvPoint3& _fTotalScale);

	OvMatrix&	Rotate(OvFloat x,OvFloat y,OvFloat z,OvFloat w);
	OvMatrix&	Rotate(const OvQuaternion& _crQuaternion);

	OvMatrix&	Translate(OvFloat x,OvFloat y,OvFloat z);
	OvMatrix&	Translate(const OvPoint3& _crTraslate);

	OvMatrix&	Inverse(OvFloat fDet = 0);

	union
	{
		struct 
		{
			OvFloat _11,_12,_13,_14;
			OvFloat _21,_22,_23,_24;
			OvFloat _31,_32,_33,_34;
			OvFloat _41,_42,_43,_44;
		};
		OvFloat m[4][4];
	};

};

OvMatrix		OvMatrixTranspose(const OvMatrix&);
OvMatrix		OvMatrixInverseMatrix(const OvMatrix&);
OvPoint3		OvMatrixExtractTraslate(const OvMatrix&);
OvQuaternion	OvMatrixExtractRotate(const OvMatrix&);
OvPoint3		OvMatrixExtractScale(const OvMatrix&);