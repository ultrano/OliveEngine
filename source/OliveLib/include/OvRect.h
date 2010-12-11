#pragma once
#include "OvTypeDef.h"
#include "OvMemObject.h"
#include "OvPoint2.h"

//////////////////////////////////////////////////////////////////////////
template<typename T>
template_class				OvTRect;
typedef OvTRect<OvInt>		OvIRect;
typedef OvTRect<OvFloat>	OvFRect;
class						OvFxRect;
//////////////////////////////////////////////////////////////////////////


template<typename T>
template_class OvTRect : public OvMemObject
{
public:
	OvTRect() : left( 0 ), top( 0 ), right( 0 ), bottom( 0 ) {};
	OvTRect(  const T& _l
			, const T& _t
			, const T& _r
			, const T& _b) 
		: left( _l )
		, top( _t )
		, right( _r )
		, bottom( _b ) {};
public:
	T left;
	T top;
	T right;
	T bottom;
};

class OvFxRect : public OvFRect
{
public:
	//////////////////////////////////////////////////////////////////////////
	OvPoint2	GetLeftTop();
	OvPoint2	GetRightBottom();
	//////////////////////////////////////////////////////////////////////////
	OvFloat		GetWidth();
	OvFloat		GetHeight();
	//////////////////////////////////////////////////////////////////////////
	OvBool		IsInSide( const OvPoint2& pt );
	OvBool		IsOutSide( const OvPoint2& pt );
	OvBool		IsOnBound( const OvPoint2& pt );
	//////////////////////////////////////////////////////////////////////////
};