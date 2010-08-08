#pragma once

#include "OvMemObject.h"
#include "OvPoint2.h"
// 
// class OvRect :public OvMemObject
// {
// public:
// 	enum eRectState
// 	{
// 		eRectState_Out,
// 		eRectState_In,
// 		eRectState_Bound
// 	};
// public:
// 	OvRect();
// 	OvRect(const OvPoint2& rPt2CenterPosition,float fWidth,float fHeight);
// 	~OvRect();
// 	void		SetWidth(float fWidth);
// 	void		SetHeight(float fHeight);
// 	float		GetWidth()const;
// 	float		GetHeight()const;
// 	void		SetCenter(const OvPoint2& pt2Center);
// 	const OvPoint2& GetCenter()const;
// 	void		SetRect(int iLeft,int iTop,int iRight,int iBottom);
// 	RECT		GetRect();
// 	int			FindRectState(const OvPoint2& pt2Point);
// 	int			FindRectState(float fX,float fY);
// 
// 	//! 지워질 가능성이 높은 메소드(임시용)
// 	OvPoint2	GetLeftTop();
// 	OvPoint2	GetLeftBottom();
// 	OvPoint2	GetRightTop();
// 	OvPoint2	GetRightBottom();
// 	//
// private:
// 	float		width;
// 	float		height;
// 	OvPoint2	center;
// };