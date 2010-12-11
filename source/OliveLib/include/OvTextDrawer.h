#pragma once

#include "OvObject.h"
#include "OvAutoPtr.h"
#include "OvRect.h"
#include "OvColor.h"
#include <d3dx9.h>

class OvRect;
class OvPoint2;
OvREF_POINTER(OvTexture);
OvREF_POINTER(OvTextDrawer);
class OvTextDrawer : public OvObject
{

public:
	OvTextDrawer();
	~OvTextDrawer();

	OvBool	BuildFont( OvUInt height, OvUInt width, OvUInt weight );

	void	Draw( const OvString& text, const OvIRect& rect, OvUInt fmt, const OvColor& color );
	void	DrawToTexture( OvTextureSPtr texture, const OvString& text, const OvIRect& rect, OvUInt fmt, const OvColor& color );
private:

	LPD3DXFONT	m_font;

};