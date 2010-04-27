// #include "OvRect.h"
// 
// OvRect::OvRect()
// {
// 
// }
// OvRect::OvRect(const OvPoint2& rPt2CenterPosition,float fWidth,float fHeight)
// :center(rPt2CenterPosition)
// ,width(fWidth)
// ,height(fHeight)
// {
// }
// OvRect::~OvRect()
// {
// 
// }
// void		OvRect::SetWidth(float fWidth)
// {
// 	width = fWidth;
// }
// void		OvRect::SetHeight(float fHeight)
// {
// 	height = fHeight;
// }
// float		OvRect::GetWidth()const
// {
// 	return width;
// }
// float		OvRect::GetHeight()const
// {
// 	return height;
// }
// 
// void			OvRect::SetCenter(const OvPoint2& pt2Center)
// {
// 	center = pt2Center;
// }
// const OvPoint2& OvRect::GetCenter()const
// {
// 	return center;
// }
// void		OvRect::SetRect(int iLeft,int iTop,int iRight,int iBottom)
// {
// 	SetWidth(iRight - iLeft);
// 	SetHeight(iBottom - iTop);
// 	SetCenter(OvPoint2((iRight + iLeft)/2.0f,(iBottom + iTop)/2.0f));
// }
// RECT		OvRect::GetRect()
// {
// 	float kfHalfH = GetHeight() / 2.0f;
// 	float kfHalfW = GetWidth()  / 2.0f;
// 	OvPoint2 kCenter = GetCenter();
// 	RECT kRt;
// 	kRt.top		=	kCenter.y - kfHalfH;
// 	kRt.bottom	=	kCenter.y + kfHalfH;
// 	kRt.left	=	kCenter.x - kfHalfW;
// 	kRt.right	=	kCenter.x + kfHalfW;
// 	return kRt;
// }
// int			OvRect::FindRectState(const OvPoint2& pt2Point)
// {
// 	float	kfXLength = fabs(center.x - pt2Point.x) * 2.0f;
// 	float	kfYLength = fabs(center.y - pt2Point.y) * 2.0f;
// 
// 	if (kfXLength > width || kfYLength > height)
// 		return OvRect::eRectState_Out;
// 
// 	if (kfXLength == width || kfYLength == height)
// 		return OvRect::eRectState_Bound;
// 
// 	return OvRect::eRectState_In;
// 	
// }
// 
// int			OvRect::FindRectState(float fX,float fY)
// {
// 	return FindRectState(OvPoint2(fX,fY));
// }
// OvPoint2	OvRect::GetLeftTop()
// {
// 	OvPoint2 kCenter = GetCenter();
// 	kCenter.x -= (width/2.0f);
// 	kCenter.y -= (height/2.0f);
// 	return kCenter;
// }
// OvPoint2	OvRect::GetLeftBottom()
// {
// 	OvPoint2 kCenter = GetCenter();
// 	kCenter.x -= (width/2.0f);
// 	kCenter.y += (height/2.0f);
// 	return kCenter;
// }
// OvPoint2	OvRect::GetRightTop()
// {
// 	OvPoint2 kCenter = GetCenter();
// 	kCenter.x += (width/2.0f);
// 	kCenter.y -= (height/2.0f);
// 	return kCenter;
// }
// OvPoint2	OvRect::GetRightBottom()
// {
// 	OvPoint2 kCenter = GetCenter();
// 	kCenter.x += (width/2.0f);
// 	kCenter.y += (height/2.0f);
// 	return kCenter;
// }