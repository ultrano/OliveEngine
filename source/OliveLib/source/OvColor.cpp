#include "OvColor.h"

OvColor::OvColor()
: color( 0 )
{

}

OvColor::OvColor( char _a, char _r, char _g, char _b )
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