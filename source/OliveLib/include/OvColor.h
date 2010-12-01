#pragma once
#include "OvTypeDef.h"
#include "OvMemObject.h"

class OvColor : public OvMemObject
{
public:
	OvColor();
	OvColor( unsigned char _a, unsigned char _r, unsigned char _g, unsigned char _b );
	OvColor( OvUInt _color );
public:
	union
	{
		struct 
		{
			unsigned char b;
			unsigned char g;
			unsigned char r;
			unsigned char a;
		};
		OvUInt color;
		unsigned char argb[4];
	};
};