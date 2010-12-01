#include "OvCollisionFinder.h"

#include "OvPoint3.h"
#include "OvPlane.h"
#include "OvSphere.h"
#include "OvBox.h"

OvBool	OvCollisionFinder::TestCollision(OvSphere& _rSphere0,OvPlane& _rPlane0)
{
	OvFloat kfLength = OvPoint3DotProduct(_rSphere0.GetCenter(),_rPlane0.GetNormal()) - _rPlane0.GetDistance();
	return (kfLength - _rSphere0.GetRadius()) <= 0;
}
OvBool	OvCollisionFinder::TestCollision(OvSphere& _rSphere0,OvPoint3& _rPoint0)
{
	OvFloat kfDistance = OvPoint3DotProduct(_rSphere0.GetCenter(),_rPoint0);
	return (_rSphere0.GetRadius() - kfDistance) <= 0;
}
OvBool	OvCollisionFinder::TestCollision(OvSphere& _rSphere0,OvSphere& _rSphere1)
{
	OvFloat kfCenterDistance = OvPoint3Length(_rSphere0.GetCenter(),_rSphere1.GetCenter());
	OvFloat kfRadiusDistance = _rSphere0.GetRadius() + _rSphere1.GetRadius();
	return (kfCenterDistance - kfRadiusDistance) <= 0;
}
OvBool	OvCollisionFinder::TestCollision(OvPlane& _rPlane0,OvPoint3& _rPoint0)
{
	OvFloat kfLength = OvPoint3DotProduct(_rPlane0.GetNormal(),_rPoint0) - _rPlane0.GetDistance();
	return (kfLength)  <= 0;
}
OvBool	OvCollisionFinder::TestCollision(OvPlane& _rPlane0,OvPlane& _rPlane1)
{
	return (_rPlane0.GetNormal() != _rPlane1.GetNormal())? true:(_rPlane0.GetDistance()==_rPlane1.GetDistance());
}


OvBool	OvCollisionFinder::TestCollision(OvBox& _rBox0,OvSphere& _rSphere0)
{
	OvPoint3 kpt3NearPt = (_rBox0.GetPosition() - _rSphere0.GetCenter()).Normalize();
	kpt3NearPt = kpt3NearPt*_rSphere0.GetRadius();
	kpt3NearPt = _rSphere0.GetCenter() + kpt3NearPt;
	for (size_t i = 0 ; i < OvBox::PLANE_COUNT ; ++i)
	{
		if (!TestCollision(_rSphere0,_rBox0.GetPlane((OvBox::BOX_PLANE)i)))
			return false;
	}
	return true;
}