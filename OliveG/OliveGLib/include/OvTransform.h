#pragma once
#include "OvPoint3.h"
#include "OvQuaternion.h"
#include "OvMatrix.h"
#include "OvMemObject.h"

class OvTransform : public OvMemObject
{

public:

	OvTransform();

	OvPoint3	Scale;
	OvQuaternion Quaternion;
	OvPoint3 Position;
	OvMatrix BuildMatrix;

};

OvMatrix MakeTransformMatrix(const OvPoint3& scale, const OvQuaternion& quat, const OvPoint3& pos);
OvMatrix MakeTransformMatrix(const OvTransform& transform);
OvTransform ExtractTransformFromMatrix( const OvMatrix& mat );