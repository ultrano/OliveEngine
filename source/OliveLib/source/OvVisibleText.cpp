// #include "OvVisibleText.h"
// #include "OvBitFlags.h"
// #include "OvRect.h"
// #include "OvRenderer.h"
// #include "OvRenderTarget.h"
// #include "OvTexture.h"
// #include "OvPoint2.h"
// #include "d3dx9.h"
// /*
// 
// --------- 기능성 옵션 ------------
// DT_END_ELLIPSIS or DT_PATH_ELLIPSIS & DT_MODIFYSTRING -- 범위 초과 문자 생략
// DT_CALCRECT - 문자가 포함되는 렉트 검사. (드로윙안된다)
// DT_NOCLIP - 렉트무시하고 드로윙
// 
// DT_EXPANDTABS - 탭의 간격을 늘린다.
// DT_RTLREADING - 아라비아어의 읽기 어순으로 드로윙 된다 (오른쪽->왼쪽)
// DT_SINGLELINE - 한줄만 쓴다.
// ----------------------------------
// 
// ------- 기본 셋팅 해야 할것들 ---
// 
// DT_HIDEPREFIX - 밑줄시행 특수 문자인 (&)를 숨긴다.(기능은 유지)
// DT_NOPREFIX - & 기능을 무시한다(기능 off)
// DT_PREFIXONLY - & 기능만 시행 된다 (기능만 on)
// ----------------------------------
// ----------- 필요 없는 셋팅 -----------
// DT_EXTERNALLEADING - 잘은 모르겠지만 글자의 크기를 확장하여 계산한다.
// DT_EDITCONTROL - 잘 모름. 필요 없는 기능인듯.
// DT_TABSTOP - 일정 문자에 대한 제제를 가한다 (기능 안쓰기로 하자)
// DT_INTERNAL - 시스템 폰트를 사용해 텍스트 메트릭스를 계산한다
// 
// DT_WORD_ELLIPSIS - 렉트를 넘어서는 단어에 생략 문자를 포함한다 (기능 안쓴다)
// --------------------------------------
// 
// ---------- 정렬 ----------
// DT_LEFT
// DT_RIGHT
// DT_CENTER
// DT_BOTTOM
// DT_TOP
// DT_VCENTER
// --------------------------
// 
// --- 개행  ---
// 
// DT_WORDBREAK
// DT_NOFULLWIDTHCHARBREAK - DBCS에 대한 잘못된 개행을 방지 한다.
// -------------
// 
// */
// 
// enum	eVTFlag
// {
// 	eVTFlag_Italic,
// 	eVTFlag_AutoLineFeed,
// };
// 
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
// 
// OvVisibleText::OvVisibleText()
// :m_pPimple(OvNew OvVisibleText::OvPimple)
// {
// 	m_pPimple->mHAlign = eTextAlignHorizon_Left;
// 	m_pPimple->mVAlign = eTextAlignVertical_Top;
// 	m_pPimple->mFont = NULL;
// 	m_pPimple->mDrawOption = 0;
// 	m_pPimple->mTextColor = D3DXCOLOR(1,1,1,1);
// 	m_pPimple->mTextRenderTarget = OvNew OvRenderTarget;
// }
// OvVisibleText::~OvVisibleText()
// {
// 	if (m_pPimple->mFont)
// 	{
// 		m_pPimple->mFont->Release();
// 	}
// }
// bool	OvVisibleText::BuildFont(const char* pStyle,int iWidth,int iHeight)
// {
// 	if (NULL == pStyle)
// 	{
// 		return false;
// 	}
// 	LPD3DXFONT	kpFont = NULL;
// 	LPDIRECT3DDEVICE9 kpDevice = NULL;
// 	kpDevice = OvRenderer::GetInstance()->GetDevice();
// 	HRESULT hr = D3DXCreateFont(kpDevice,
// 		iHeight,
// 		iWidth,
// 		FW_HEAVY,
// 		1,
// 		false,
// 		DEFAULT_CHARSET,
// 		OUT_DEFAULT_PRECIS,
// 		DEFAULT_QUALITY,
// 		DEFAULT_PITCH | FF_DONTCARE,
// 		pStyle,
// 		&kpFont);
// 	if (FAILED(hr) || NULL == kpFont)
// 	{
// 		return false;
// 	}
// 	if (m_pPimple->mFont)
// 	{
// 		m_pPimple->mFont->Release();
// 	}
// 	m_pPimple->mFont = kpFont;
// 	m_pPimple->mStyle = pStyle;
// }
// void	OvVisibleText::SetAlignHorizon(OvVisibleText::eTextAlignHorizon eAlign)
// {
// 	m_pPimple->mHAlign = eAlign;
// 	switch(eAlign)
// 	{
// 	case eTextAlignHorizon_Left :
// 		m_pPimple->mDrawOption |= DT_LEFT;
// 		break;
// 	case eTextAlignHorizon_Right :
// 		m_pPimple->mDrawOption |= DT_RIGHT;
// 		break;
// 	case eTextAlignHorizon_Center :
// 		m_pPimple->mDrawOption |= DT_CENTER;
// 		break;
// 	}
// }
// void	OvVisibleText::SetAlignVertical(OvVisibleText::eTextAlignVertical eAlign)
// {
// 	m_pPimple->mVAlign = eAlign;
// 	switch(eAlign)
// 	{
// 	case eTextAlignVertical_Top :
// 		m_pPimple->mDrawOption |= DT_TOP;
// 		break;
// 	case eTextAlignVertical_Bottom :
// 		m_pPimple->mDrawOption |= DT_BOTTOM;
// 		break;
// 	case eTextAlignVertical_Center :
// 		m_pPimple->mDrawOption |= DT_VCENTER;
// 		break;
// 	}
// }
// int		OvVisibleText::GetAlignHorizon()
// {
// 	return m_pPimple->mHAlign;
// }
// int		OvVisibleText::GetAlignVertical()
// {
// 	return m_pPimple->mVAlign;
// }
// void	OvVisibleText::SetText(const char* pText)
// {
// 	if (pText)
// 	{
// 		m_pPimple->mText = pText;
// 	}
// }
// const char* OvVisibleText::GetText()
// {
// 	return m_pPimple->mText.data();
// }
// void	OvVisibleText::SetTextColor(float r,float g,float b,float a)
// {
// 	m_pPimple->mTextColor = D3DXCOLOR(r,g,b,a);
// }
// void		OvVisibleText::SetPosition(OvPoint2& pt2Pos)
// {
// 	m_pPimple->mPosition = pt2Pos;
// }
// void		OvVisibleText::SetPosition(float fx,float fy)
// {
// 	SetPosition(OvPoint2(fx,fy));
// }
// void		OvVisibleText::SetWidth(float fWidth)
// {
// 	m_pPimple->mWidth	=	fWidth;
// }
// void		OvVisibleText::SetHeight(float fHeight)
// {
// 	m_pPimple->mHeight = fHeight;
// }
// const OvPoint2& OvVisibleText::GetPosition()
// {
// 	return m_pPimple->mPosition;
// }
// float			OvVisibleText::GetWidth()
// {
// 	return m_pPimple->mWidth;
// }
// float			OvVisibleText::GetHeight()
// {
// 	return m_pPimple->mHeight;
// }
// RECT		OvVisibleText::GetRect()
// {
// 	RECT	kRt;
// 	kRt.top		=	m_pPimple->mPosition.x;
// 	kRt.left	=	m_pPimple->mPosition.y;
// 	kRt.right	=	m_pPimple->mPosition.x + GetWidth();
// 	kRt.bottom	=	m_pPimple->mPosition.y + GetHeight();
// 	return kRt;
// }
// void	OvVisibleText::SetItalicStyle(bool bCheck)
// {
// 	m_pPimple->mFontOption.SetFlag(eVTFlag_Italic,bCheck);
// }
// void	OvVisibleText::SetAutoLineFeed(bool bCheck)
// {
// 	m_pPimple->mFontOption.SetFlag(eVTFlag_AutoLineFeed,bCheck);
// 	if (bCheck)
// 	{
// 		m_pPimple->mDrawOption |= DT_WORDBREAK;
// 	}
// 	else
// 	{
// 		m_pPimple->mDrawOption &= ~DT_WORDBREAK;
// 	}
// }
// void	OvVisibleText::Render()
// {
// 	string&	kText = m_pPimple->mText;
// 	DWORD kdDrawOpt = m_pPimple->mDrawOption;
// 	RECT	kRt = GetRect();
// 	m_pPimple->mFont->DrawText(NULL,kText.data(),kText.size(),&kRt,kdDrawOpt,m_pPimple->mTextColor);
// }
// void	OvVisibleText::RenderToTexture(OvTextureSPtr pTexture)
// {
// 	/*if (pTexture && m_pPimple->mTextRenderTarget)
// 	{
// 		m_pPimple->mTextRenderTarget->SetTargetTexture(pTexture);
// 		if (OvRenderer::GetInstance()->BeginRenderTarget(m_pPimple->mTextRenderTarget))
// 		{
// 			OvRenderer::GetInstance()->ClearTarget();
// 			OvRenderer::GetInstance()->BeginTarget();
// 
// 			Render();
// 
// 			OvRenderer::GetInstance()->EndTarget();
// 			OvRenderer::GetInstance()->EndRenderTarget();
// 		}
// 	}*/
// }