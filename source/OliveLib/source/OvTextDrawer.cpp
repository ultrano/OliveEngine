#include "OvTextDrawer.h"
#include "OvBitFlags.h"
#include "OvRenderer.h"
#include "OvTexture.h"
/*

--------- 기능성 옵션 ------------
DT_END_ELLIPSIS or DT_PATH_ELLIPSIS & DT_MODIFYSTRING -- 범위 초과 문자 생략
DT_CALCRECT - 문자가 포함되는 렉트 검사. (드로윙안된다)
DT_NOCLIP - 렉트무시하고 드로윙

DT_EXPANDTABS - 탭의 간격을 늘린다.
DT_RTLREADING - 아라비아어의 읽기 어순으로 드로윙 된다 (오른쪽->왼쪽)
DT_SINGLELINE - 한줄만 쓴다.
----------------------------------

------- 기본 셋팅 해야 할것들 ---

DT_HIDEPREFIX - 밑줄시행 특수 문자인 (&)를 숨긴다.(기능은 유지)
DT_NOPREFIX - & 기능을 무시한다(기능 off)
DT_PREFIXONLY - & 기능만 시행 된다 (기능만 on)
----------------------------------
----------- 필요 없는 셋팅 -----------
DT_EXTERNALLEADING - 잘은 모르겠지만 글자의 크기를 확장하여 계산한다.
DT_EDITCONTROL - 잘 모름. 필요 없는 기능인듯.
DT_TABSTOP - 일정 문자에 대한 제제를 가한다 (기능 안쓰기로 하자)
DT_INTERNAL - 시스템 폰트를 사용해 텍스트 메트릭스를 계산한다

DT_WORD_ELLIPSIS - 렉트를 넘어서는 단어에 생략 문자를 포함한다 (기능 안쓴다)
--------------------------------------

---------- 정렬 ----------
DT_LEFT
DT_RIGHT
DT_CENTER
DT_BOTTOM
DT_TOP
DT_VCENTER
--------------------------

--- 개행  ---

DT_WORDBREAK
DT_NOFULLWIDTHCHARBREAK - DBCS에 대한 잘못된 개행을 방지 한다.
-------------

*/

enum	eVTFlag
{
	eVTFlag_Italic,
	eVTFlag_AutoLineFeed,
};


// struct OvVisibleText::OvPimple : OvMemObject
// {
// 	LPD3DXFONT			mFont;
// 	DWORD 				mFontWitdh;
// 	DWORD 				mFontHeight;
// 	DWORD 				mFontWeight;
// 	Ov8SetFlags			mFontOption;
// 	DWORD 				mCharSet;
// 	string				mStyle;
// 	D3DXCOLOR			mTextColor;
// 	eTextAlignHorizon  	mHAlign;
// 	eTextAlignVertical 	mVAlign;
// 	string				mText;
// 	DWORD				mDrawOption;
// 	OvPoint2			mPosition;
// 	float				mWidth,mHeight;
// 	OvRenderTargetSPtr	mTextRenderTarget;
// 
// };
OvTextDrawer::OvTextDrawer()
: m_font( NULL )
{
}
OvTextDrawer::~OvTextDrawer()
{
	if ( m_font )
	{
		m_font->Release();
	}
}

OvBool OvTextDrawer::BuildFont( OvUInt height, OvUInt width, OvUInt weight )
{
	if ( m_font )
	{
		m_font->Release();
	}
	OvDevice device = OvRenderer::GetInstance()->GetDevice();

	OvUInt miplevel = 1;
	OvBool italic = false;
	OvUInt charset = DEFAULT_CHARSET;
	OvUInt outputprecision = OUT_CHARACTER_PRECIS;
	OvUInt quality = DEFAULT_QUALITY;
	OvUInt pitchNfamily = DEFAULT_PITCH | FF_DONTCARE;
	OvString facename = "굴림체";

	HRESULT hr = D3DXCreateFont
					( device
				  	, height			//!< 글자 높이
				  	, width				//!< 글자 넓이
				  	, weight			//!< 글자 두께
				  	, miplevel			//!< 밉맵 레벨
				  	, italic			//!< 글자 기울기 설정
				  	, charset			//!< 문자코드와 문자의 대응관계정의
				  	, outputprecision	//!< 출력 정확도 설정.
				  	, quality			//!< 퀄리티
				  	, pitchNfamily		//!< 폰트 피치 설정.
				  	, facename.c_str()	//!< 글꼴
				  	, &m_font
				  	);
	return SUCCEEDED( hr );
}

void OvTextDrawer::Draw( const OvString& text, const OvIRect& rect, OvUInt fmt, const OvColor& color )
{
	if ( m_font )
	{
		m_font->DrawTextA( NULL, text.c_str(), -1, (LPRECT)&rect, fmt, (D3DCOLOR)color.color );
	}
}

void OvTextDrawer::DrawToTexture( OvTextureSPtr texture, const OvString& text, const OvIRect& rect, OvUInt fmt, const OvColor& color )
{
	if ( OvRenderer* renderer = OvRenderer::GetInstance() )
	{
		renderer->SetRenderTarget( texture, false, false );
		Draw( text, rect, fmt, color );
		renderer->SetRenderTarget( NULL );
	}
}