#include "OvColor.h"

OvColor::OvColor()
: color( 0 )
{

}

OvColor::OvColor( unsigned char _a, unsigned char _r, unsigned char _g, unsigned char _b )
: a( _a )
, r( _r )
, g( _g )
, b( _b )
{

}

OvColor::OvColor( unsigned int _color )
: color( _color )
{

}