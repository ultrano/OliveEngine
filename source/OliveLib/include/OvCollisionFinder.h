#pragma once
#include "OvTypeDef.h"

class OvSphere ;
class OvPlane;
class  OvPoint3;
class OvBox;

namespace OvCollisionFinder
{

OvBool	TestCollision(OvSphere& _rSphere0,OvPlane& _rPlane0);
OvBool	TestCollision(OvSphere& _rSphere0,OvPoint3& _rPoint0);
OvBool	TestCollision(OvSphere& _rSphere0,OvSphere& _rSphere1);
OvBool	TestCollision(OvPlane& _rPlane0,OvPoint3& _rPoint0);
OvBool	TestCollision(OvPlane& _rPlane0,OvPlane& _rPlane1);
OvBool	TestCollision(OvBox& _rBox0,OvSphere& _rSphere0);
};