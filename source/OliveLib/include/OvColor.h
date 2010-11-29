#pragma once
#include "OvMemObject.h"

class OvColor : public OvMemObject
{
public:
	OvColor();
	OvColor( char _a, char _r, char _g, char _b );
	OvColor( unsigned int _color );
public:
	union
	{
		struct 
		{
			char a;
			char r;
			char g;
			char b;
		};
		unsigned int color;
		char argb[4];
	};
};