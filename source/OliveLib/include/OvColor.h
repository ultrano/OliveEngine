#pragma once
#include "OvTypeDef.h"
#include "OvMemObject.h"

class OvColor : public OvMemObject
{
public:
	OvColor();
	OvColor( OvByte _a, OvByte _r, OvByte _g, OvByte _b );
	OvColor( OvUInt _color );
public:
	union
	{
		struct 
		{
			OvByte b;
			OvByte g;
			OvByte r;
			OvByte a;
		};
		OvUInt color;
		OvByte argb[4];
	};
};