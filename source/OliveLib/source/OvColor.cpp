#include "OvColor.h"

OvColor::OvColor()
: color( 0 )
{

}

OvColor::OvColor( OvByte _a, OvByte _r, OvByte _g, OvByte _b )
: a( _a )
, r( _r )
, g( _g )
, b( _b )
{

}

OvColor::OvColor( OvUInt _color )
: color( _color )
{

}