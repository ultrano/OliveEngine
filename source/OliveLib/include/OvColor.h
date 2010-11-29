#pragma once
#include "OvMemObject.h"

class OvColor : public OvMemObject
{
public:
	OvColor();
	OvColor( unsigned char _a, unsigned char _r, unsigned char _g, unsigned char _b );
	OvColor( unsigned int _color );
public:
	union
	{
		struct 
		{
			unsigned char a;
			unsigned char r;
			unsigned char g;
			unsigned char b;
		};
		unsigned int color;
		unsigned char argb[4];
	};
};