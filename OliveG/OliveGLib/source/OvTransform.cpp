#include "OvTransform.h"
#include <d3dx9.h>

OvTransform::OvTransform()
:Scale(1,1,1)
{
}

void	OvTransform::BuildTransformMatrix()
{
	OvMatrix kSupportMat;

	kSupportMat.Identity();
	BuildMatrix.Identity();

	BuildMatrix = BuildMatrix * kSupportMat.Scale(Scale.x,Scale.y,Scale.z);
	kSupportMat.Identity();
	BuildMatrix = BuildMatrix * kSupportMat.Rotate(Quaternion);
	kSupportMat.Identity();
	BuildMatrix = BuildMatrix * kSupportMat.Translate(Position);
}


void	OvTransform::ExtractTransformFromBuildMatrix()
{
	Position.x = BuildMatrix._41;
	Position.y = BuildMatrix._42;
	Position.z = BuildMatrix._43;

	OvMatrix kExtractMat;
	D3DXQuaternionRotationMatrix((D3DXQUATERNION*)&Quaternion,(D3DXMATRIX*)&BuildMatrix);
	kExtractMat = BuildMatrix*OvMatrix().Rotate(Quaternion.Inverse());

	Scale.x = kExtractMat._11;
	Scale.y = kExtractMat._22;
	Scale.z = kExtractMat._33;

}