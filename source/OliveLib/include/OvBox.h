#pragma once
#include "OvQuaternion.h"
#include "OvPoint3.h"
#include "OvPlane.h"
class OvBox
{
public:
	enum BOX_PLANE
	{
		LEFT,
		RIGHT,
		TOP,
		BOTTOM,
		FRONT,
		BACK,
		PLANE_COUNT
	};

	OvBox();
	~OvBox();

	OvPoint3	GetAxisX();
	OvPoint3	GetAxisY();
	OvPoint3	GetAxisZ();
	OvPlane		GetPlane(BOX_PLANE _iSideIndex);

	void	SetPosition(OvPoint3& _rPosition);
	const OvPoint3&	GetPosition()const;

private:

	OvPoint3	m_pt3HalfSizeAxis[3];
	OvPoint3	m_pt3Position;

};