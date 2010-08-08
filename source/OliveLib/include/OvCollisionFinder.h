#pragma once

class OvSphere ;
class OvPlane;
class  OvPoint3;
class OvBox;

namespace OvCollisionFinder
{

bool	TestCollision(OvSphere& _rSphere0,OvPlane& _rPlane0);
bool	TestCollision(OvSphere& _rSphere0,OvPoint3& _rPoint0);
bool	TestCollision(OvSphere& _rSphere0,OvSphere& _rSphere1);
bool	TestCollision(OvPlane& _rPlane0,OvPoint3& _rPoint0);
bool	TestCollision(OvPlane& _rPlane0,OvPlane& _rPlane1);
bool	TestCollision(OvBox& _rBox0,OvSphere& _rSphere0);
};