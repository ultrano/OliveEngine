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

//! 일단 아직 이런 글로벌 함수들에 위한 장소가 정립되어 있지 않아서
//! 살발되어 있는데, 지금은 이대로 쓰고 나중에 한곳에 모아두도록 한다.
OvMatrix	MakeTransformMatrix(const OvPoint3& scale, const OvQuaternion& quat, const OvPoint3& pos);
OvMatrix	MakeTransformMatrix(const OvTransform& transform);
OvTransform ExtractTransformFromMatrix( const OvMatrix& mat );
OvBool		MakeViewMatrix( const OvPoint3& lookDir, const OvPoint3& upDir, const OvPoint3& pos, OvMatrix& outMat );
