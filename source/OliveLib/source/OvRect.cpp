#include "OvRect.h"

OvPoint2 OvFxRect::GetLeftTop()
{
	return OvPoint2( left, top );
}

OvPoint2 OvFxRect::GetRightBottom()
{
	return OvPoint2( right, bottom );
}

OvFloat OvFxRect::GetWidth()
{
	return ( right - left );
}

OvFloat OvFxRect::GetHeight()
{
	return ( bottom - top );
}

OvBool OvFxRect::IsInSide( const OvPoint2& pt )
{
	OvFloat width = ( pt.x - left );
	OvFloat height = ( pt.y - top );
	OvBool def = ( width > 0 && height > 0 );

	def = def && ( width < GetWidth() ) && ( height < GetHeight() );

	return def;
}

OvBool OvFxRect::IsOutSide( const OvPoint2& pt )
{
	OvFloat width = ( pt.x - left );
	OvFloat height = ( pt.y - top );
	OvBool def = ( width < 0 || height < 0 );

	def = def || ( width > GetWidth() ) || ( height > GetHeight() );

	return def;
}

OvBool OvFxRect::IsOnBound( const OvPoint2& pt )
{
	OvFloat def = ( ( pt.x - left ) * ( pt.y - top ) );
	return ( def == 0 );
}