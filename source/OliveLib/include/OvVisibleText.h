// #pragma once
// 
// #include "OvRefBase.h"
// #include "OvAutoPtr.h"
// 
// class OvRect;
// class OvPoint2;
// OvREF_POINTER(OvTexture);
// OvREF_POINTER(OvVisibleText);
// class OvVisibleText : public OvRefBase
// {
// 
// public:
// 	enum	eTextAlignHorizon
// 	{
// 		eTextAlignHorizon_Left,
// 		eTextAlignHorizon_Right,
// 		eTextAlignHorizon_Center
// 	};
// 	enum	eTextAlignVertical
// 	{
// 		eTextAlignVertical_Top,
// 		eTextAlignVertical_Bottom,
// 		eTextAlignVertical_Center
// 	};
// 
// 	OvVisibleText();
// 	~OvVisibleText();
// 
// 	bool	BuildFont(const char* pStyle,int iWidth=0,int iHeight=0);
// 
// 	void	SetAlignHorizon(eTextAlignHorizon eAlign);
// 	void	SetAlignVertical(eTextAlignVertical eAlign);
// 	int		GetAlignHorizon();
// 	int		GetAlignVertical();
// 
// 	void		SetText(const char* pText);
// 	const char* GetText();
// 	
// 	void		SetTextColor(float r,float g,float b,float a);
// 	
// 	void			SetPosition(OvPoint2& pt2Pos);
// 	void			SetPosition(float fx,float fy);
// 	void			SetWidth(float fWidth);
// 	void			SetHeight(float fHeight);
// 	const OvPoint2& GetPosition();
// 	float			GetWidth();
// 	float			GetHeight();
// 	RECT			GetRect();
// 
// 	void		SetItalicStyle(bool bCheck);
// 	void		SetAutoLineFeed(bool bCheck);
// 
// 	void	Render();
// 	void	RenderToTexture(OvTextureSPtr pTexture);
// 
// private:
// 	struct OvPimple;
// 	OvAutoPtr< OvPimple> m_pPimple;
// };