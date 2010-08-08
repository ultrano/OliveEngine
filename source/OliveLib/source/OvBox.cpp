#include "OvBox.h"

OvBox::OvBox()
{
	m_pt3HalfSizeAxis[0] = OvPoint3(1,0,0);
	m_pt3HalfSizeAxis[1] = OvPoint3(0,1,0);
	m_pt3HalfSizeAxis[2] = OvPoint3(0,0,1);
	m_pt3Position = OvPoint3(0,0,0);
}

OvBox::~OvBox()
{

}

OvPoint3	OvBox::GetAxisX()
{
	return m_pt3HalfSizeAxis[0].Normalize();
}
OvPoint3	OvBox::GetAxisY()
{
	return m_pt3HalfSizeAxis[1].Normalize();
}
OvPoint3	OvBox::GetAxisZ()
{
	return m_pt3HalfSizeAxis[2].Normalize();
}
OvPlane OvBox::GetPlane(BOX_PLANE _iSideIndex)
{
	OvPoint3 kNormal;
	float	kfDistance;

	switch(_iSideIndex)
	{
	case BOX_PLANE::RIGHT : 
		kNormal = m_pt3HalfSizeAxis[0];
		kfDistance = m_pt3HalfSizeAxis[0].Length();
		break;

	case BOX_PLANE::LEFT : 
		kNormal = -m_pt3HalfSizeAxis[0];
		kfDistance = m_pt3HalfSizeAxis[0].Length();
		break;

	case BOX_PLANE::FRONT :
		kNormal = m_pt3HalfSizeAxis[1];
		kfDistance = m_pt3HalfSizeAxis[1].Length(); 
		break;

	case BOX_PLANE::BACK : 
		kNormal = -m_pt3HalfSizeAxis[1];
		kfDistance = m_pt3HalfSizeAxis[1].Length(); 
		break;

	case BOX_PLANE::TOP : 
		kNormal = m_pt3HalfSizeAxis[2];
		kfDistance = m_pt3HalfSizeAxis[2].Length(); 
		break;

	case BOX_PLANE::BOTTOM : 
		kNormal = -m_pt3HalfSizeAxis[2];
		kfDistance = m_pt3HalfSizeAxis[2].Length();
		break;

	}
	return OvPlane(kNormal,kfDistance);
}

void	OvBox::SetPosition(OvPoint3& _rPosition)
{
	m_pt3Position = _rPosition;
}

const OvPoint3&	OvBox::GetPosition()const
{
	return m_pt3Position;
}