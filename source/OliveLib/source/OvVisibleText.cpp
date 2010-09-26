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
// --------- ��ɼ� �ɼ� ------------
// DT_END_ELLIPSIS or DT_PATH_ELLIPSIS & DT_MODIFYSTRING -- ���� �ʰ� ���� ����
// DT_CALCRECT - ���ڰ� ���ԵǴ� ��Ʈ �˻�. (������ȵȴ�)
// DT_NOCLIP - ��Ʈ�����ϰ� �����
// 
// DT_EXPANDTABS - ���� ������ �ø���.
// DT_RTLREADING - �ƶ��ƾ��� �б� ������� ����� �ȴ� (������->����)
// DT_SINGLELINE - ���ٸ� ����.
// ----------------------------------
// 
// ------- �⺻ ���� �ؾ� �Ұ͵� ---
// 
// DT_HIDEPREFIX - ���ٽ��� Ư�� ������ (&)�� �����.(����� ����)
// DT_NOPREFIX - & ����� �����Ѵ�(��� off)
// DT_PREFIXONLY - & ��ɸ� ���� �ȴ� (��ɸ� on)
// ----------------------------------
// ----------- �ʿ� ���� ���� -----------
// DT_EXTERNALLEADING - ���� �𸣰����� ������ ũ�⸦ Ȯ���Ͽ� ����Ѵ�.
// DT_EDITCONTROL - �� ��. �ʿ� ���� ����ε�.
// DT_TABSTOP - ���� ���ڿ� ���� ������ ���Ѵ� (��� �Ⱦ���� ����)
// DT_INTERNAL - �ý��� ��Ʈ�� ����� �ؽ�Ʈ ��Ʈ������ ����Ѵ�
// 
// DT_WORD_ELLIPSIS - ��Ʈ�� �Ѿ�� �ܾ ���� ���ڸ� �����Ѵ� (��� �Ⱦ���)
// --------------------------------------
// 
// ---------- ���� ----------
// DT_LEFT
// DT_RIGHT
// DT_CENTER
// DT_BOTTOM
// DT_TOP
// DT_VCENTER
// --------------------------
// 
// --- ����  ---
// 
// DT_WORDBREAK
// DT_NOFULLWIDTHCHARBREAK - DBCS�� ���� �߸��� ������ ���� �Ѵ�.
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