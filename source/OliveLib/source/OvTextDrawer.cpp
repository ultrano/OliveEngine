#include "OvTextDrawer.h"
#include "OvBitFlags.h"
#include "OvRenderer.h"
#include "OvTexture.h"
/*

--------- ��ɼ� �ɼ� ------------
DT_END_ELLIPSIS or DT_PATH_ELLIPSIS & DT_MODIFYSTRING -- ���� �ʰ� ���� ����
DT_CALCRECT - ���ڰ� ���ԵǴ� ��Ʈ �˻�. (������ȵȴ�)
DT_NOCLIP - ��Ʈ�����ϰ� �����

DT_EXPANDTABS - ���� ������ �ø���.
DT_RTLREADING - �ƶ��ƾ��� �б� ������� ����� �ȴ� (������->����)
DT_SINGLELINE - ���ٸ� ����.
----------------------------------

------- �⺻ ���� �ؾ� �Ұ͵� ---

DT_HIDEPREFIX - ���ٽ��� Ư�� ������ (&)�� �����.(����� ����)
DT_NOPREFIX - & ����� �����Ѵ�(��� off)
DT_PREFIXONLY - & ��ɸ� ���� �ȴ� (��ɸ� on)
----------------------------------
----------- �ʿ� ���� ���� -----------
DT_EXTERNALLEADING - ���� �𸣰����� ������ ũ�⸦ Ȯ���Ͽ� ����Ѵ�.
DT_EDITCONTROL - �� ��. �ʿ� ���� ����ε�.
DT_TABSTOP - ���� ���ڿ� ���� ������ ���Ѵ� (��� �Ⱦ���� ����)
DT_INTERNAL - �ý��� ��Ʈ�� ����� �ؽ�Ʈ ��Ʈ������ ����Ѵ�

DT_WORD_ELLIPSIS - ��Ʈ�� �Ѿ�� �ܾ ���� ���ڸ� �����Ѵ� (��� �Ⱦ���)
--------------------------------------

---------- ���� ----------
DT_LEFT
DT_RIGHT
DT_CENTER
DT_BOTTOM
DT_TOP
DT_VCENTER
--------------------------

--- ����  ---

DT_WORDBREAK
DT_NOFULLWIDTHCHARBREAK - DBCS�� ���� �߸��� ������ ���� �Ѵ�.
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
	OvString facename = "����ü";

	HRESULT hr = D3DXCreateFont
					( device
				  	, height			//!< ���� ����
				  	, width				//!< ���� ����
				  	, weight			//!< ���� �β�
				  	, miplevel			//!< �Ӹ� ����
				  	, italic			//!< ���� ���� ����
				  	, charset			//!< �����ڵ�� ������ ������������
				  	, outputprecision	//!< ��� ��Ȯ�� ����.
				  	, quality			//!< ����Ƽ
				  	, pitchNfamily		//!< ��Ʈ ��ġ ����.
				  	, facename.c_str()	//!< �۲�
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