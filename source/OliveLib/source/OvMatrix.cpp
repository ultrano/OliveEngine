#include "OvMatrix.h"
#include <memory.h>
#include <d3dx9.h>
#include "OvPoint3.h"
#include "OvQuaternion.h"

//! Constructor
OvMatrix::OvMatrix()
{
	Identity();
};

OvMatrix::OvMatrix(const OvMatrix& _crMat )
{
	memcpy((void*)this,(void*)&_crMat,sizeof(OvMatrix));
}
OvMatrix::OvMatrix
(float k11,float k12,float k13,float k14
 ,float k21,float k22,float k23,float k24
 ,float k31,float k32,float k33,float k34
 ,float k41,float k42,float k43,float k44)
 :_11(k11),_12(k12),_13(k13),_14(k14)
 ,_21(k21),_22(k22),_23(k23),_24(k24)
 ,_31(k31),_32(k32),_33(k33),_34(k34)
 ,_41(k41),_42(k42),_43(k43),_44(k44)
{
};

//! Operator Overload
OvMatrix	OvMatrix::operator * (const OvMatrix& _crMat)
{
	OvMatrix	kOutputMat;
	D3DXMatrixMultiply((D3DXMATRIX*)&kOutputMat,(D3DXMATRIX*)this,(D3DXMATRIX*)&_crMat);
	return kOutputMat;
}

OvMatrix	OvMatrix::operator * (float _fValue)
{
	OvMatrix	kOutputMat(*this);
	float* kfpMatValue = (float*)&kOutputMat;
	for (OvInt i=0;i<16;++i)
	{
		kfpMatValue[i] = kfpMatValue[i] * _fValue;
	}
	return kOutputMat;
}
OvMatrix	operator * (const OvMatrix& argMat1, const OvMatrix& argMat2)
{
	return ((OvMatrix&)argMat1) * argMat2;
}
OvMatrix operator * (float _fValue, const OvMatrix& _crMat)
{
	OvMatrix	kOutputMat(_crMat);
	float* kfpOutputMatValue = (float*)&kOutputMat;
	for (OvInt i=0;i<16;++i)
	{
		kfpOutputMatValue[i] = kfpOutputMatValue[i] * _fValue;
	}
	return kOutputMat;
}

OvMatrix&	OvMatrix::Identity()
{
	D3DXMatrixIdentity((D3DXMATRIX*)this);
	return *this;
}

//! Build Scale
OvMatrix&	OvMatrix::Scale(float _fTotalScale)
{
	D3DXMatrixScaling((D3DXMATRIX*)this,_fTotalScale,_fTotalScale,_fTotalScale);
	return *this;
}
OvMatrix&	OvMatrix::Scale(float x,float y,float z)
{
	D3DXMatrixScaling((D3DXMATRIX*)this,x,y,z);
	return *this;
}
OvMatrix&	OvMatrix::Scale(const OvPoint3& _fTotalScale)
{
	D3DXMatrixScaling((D3DXMATRIX*)this,_fTotalScale.x,_fTotalScale.y,_fTotalScale.z);
	return *this;
}

//! Build Rotate
OvMatrix&	OvMatrix::Rotate(float x,float y,float z,float w)
{
	Rotate(OvQuaternion(x,y,z,w));
	return *this;
}
OvMatrix&	OvMatrix::Rotate(const OvQuaternion& _crQuaternion)
{
	D3DXMatrixRotationQuaternion((D3DXMATRIX*)this,(D3DXQUATERNION*)&_crQuaternion);
	return *this;
}

//! Build Translate
OvMatrix&	OvMatrix::Translate(float x,float y,float z)
{
	D3DXMatrixTranslation((D3DXMATRIX*)this,x,y,z);
	return *this;
}

OvMatrix&	OvMatrix::Translate(const OvPoint3& _crTraslate)
{
	Translate(_crTraslate.x,_crTraslate.y,_crTraslate.z);
	return *this;
}
OvMatrix		OvMatrixTranspose(const OvMatrix& rMat)
{
	OvMatrix	kRetMat;
	D3DXMatrixTranspose((D3DXMATRIX*)&kRetMat,(D3DXMATRIX*)&rMat);
	return kRetMat;
}
OvMatrix	OvMatrixInverseMatrix(const OvMatrix& rMat)
{
	OvMatrix	kRetMat;
	D3DXMatrixInverse((D3DXMATRIX*)&kRetMat,0,(D3DXMATRIX*)&rMat);
	return kRetMat;
}

OvPoint3	OvMatrixExtractTraslate(const OvMatrix& rMat)
{
	return OvPoint3(rMat._41,rMat._42,rMat._43);
}

OvQuaternion	OvMatrixExtractRotate(const OvMatrix& rMat)
{
	OvQuaternion kQuaternion;
	D3DXQuaternionRotationMatrix((D3DXQUATERNION*)&kQuaternion,(D3DXMATRIX*)&rMat);
	return kQuaternion;
}

OvPoint3		OvMatrixExtractScale(const OvMatrix& rMat)
{
	OvQuaternion kQuaternion;
	OvMatrix kExtractMat;
	D3DXQuaternionRotationMatrix((D3DXQUATERNION*)&kQuaternion,(D3DXMATRIX*)&rMat);
	kExtractMat = rMat*OvMatrix().Rotate(kQuaternion.Inverse());

	return OvPoint3(kExtractMat._41,kExtractMat._42,kExtractMat._43);
}