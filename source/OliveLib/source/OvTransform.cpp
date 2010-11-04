#include "OvTransform.h"
#include <d3dx9.h>

OvTransform::OvTransform()
:Scale(1,1,1)
{
}

OvMatrix MakeTransformMatrix( const OvPoint3& scale, const OvQuaternion& quat, const OvPoint3& pos )
{
	OvMatrix kSupportMat;
	OvMatrix BuildMatrix;

	kSupportMat.Identity();
	BuildMatrix.Identity();

	BuildMatrix = BuildMatrix * kSupportMat.Scale(scale.x,scale.y,scale.z);
	kSupportMat.Identity();
	BuildMatrix = BuildMatrix * kSupportMat.Rotate(quat);
	kSupportMat.Identity();
	BuildMatrix = BuildMatrix * kSupportMat.Translate(pos);
	return BuildMatrix;
};
OvMatrix MakeTransformMatrix( const OvTransform& transform )
{
	return MakeTransformMatrix( transform.Scale, transform.Quaternion, transform.Position );
}
OvTransform ExtractTransformFromMatrix( const OvMatrix& mat )
{
	OvTransform outPut;
	outPut.Position.x = mat._41;
	outPut.Position.y = mat._42;
	outPut.Position.z = mat._43;

	OvMatrix kExtractMat;
	D3DXQuaternionRotationMatrix((D3DXQUATERNION*)&outPut.Quaternion,(D3DXMATRIX*)&mat);
	kExtractMat = mat*OvMatrix().Rotate(outPut.Quaternion.Inverse());

	outPut.Scale.x = kExtractMat._11;
	outPut.Scale.y = kExtractMat._22;
	outPut.Scale.z = kExtractMat._33;
	return outPut;
}

bool MakeViewMatrix( const OvPoint3& lookDir, const OvPoint3& upDir, const OvPoint3& pos, OvMatrix& outMat )
{
	OvPoint3 rightDir = OvPoint3CrossProduct( upDir, lookDir );

	outMat = OvMatrix
		(rightDir.x,upDir.x,lookDir.x,0
		,rightDir.y,upDir.y,lookDir.y,0
		,rightDir.z,upDir.z,lookDir.z,0
		,-OvPoint3DotProduct( rightDir, pos ),-OvPoint3DotProduct( upDir, pos ),-OvPoint3DotProduct( lookDir, pos ),1);

	return true;
}