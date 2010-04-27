#pragma once
#include "OvPoint3.h"
#include "OvQuaternion.h"
#include "OvMatrix.h"
#include "OvMemObject.h"

class OvTransform 
{

public:

	OvTransform();

	void	BuildTransformMatrix();
	void	ExtractTransformFromBuildMatrix();

	OvPoint3	Scale;
	OvQuaternion Quaternion;
	OvPoint3 Position;
	OvMatrix BuildMatrix;

};