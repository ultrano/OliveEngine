#pragma once
#include "OvPoint3.h"
#include "OvQuaternion.h"


//typedef	D3DXMATRIXA16	OvMatrix;
class OvMatrix
{
public:

	OvMatrix();
	OvMatrix(const OvMatrix& );
	OvMatrix
		(float k11,float k12,float k13,float k14
		,float k21,float k22,float k23,float k24
		,float k31,float k32,float k33,float k34
		,float k41,float k42,float k43,float k44);

	OvMatrix	operator * (const OvMatrix&);
	OvMatrix	operator * (float );

	friend OvMatrix operator * (float, const OvMatrix& );
	friend OvMatrix operator * (const OvMatrix&, const OvMatrix& );

	OvMatrix&	Identity();

	OvMatrix&	Scale(float _fTotalScale);
	OvMatrix&	Scale(float x,float y,float z);
	OvMatrix&	Scale(const OvPoint3& _fTotalScale);

	OvMatrix&	Rotate(float x,float y,float z,float w);
	OvMatrix&	Rotate(const OvQuaternion& _crQuaternion);

	OvMatrix&	Translate(float x,float y,float z);
	OvMatrix&	Translate(const OvPoint3& _crTraslate);

	OvMatrix&	Inverse(float fDet = 0);

	union
	{
		struct 
		{
			float _11,_12,_13,_14;
			float _21,_22,_23,_24;
			float _31,_32,_33,_34;
			float _41,_42,_43,_44;
		};
		float m[4][4];
	};

};

OvMatrix		OvMatrixTranspose(const OvMatrix&);
OvMatrix		OvMatrixInverseMatrix(const OvMatrix&);
OvPoint3		OvMatrixExtractTraslate(const OvMatrix&);
OvQuaternion	OvMatrixExtractRotate(const OvMatrix&);
OvPoint3		OvMatrixExtractScale(const OvMatrix&);