#pragma once
#include <string>
#include <d3dx9.h>

class OvShaderCodeIncluder : public ID3DXInclude
{
public:
	OvShaderCodeIncluder();
	STDMETHOD(Open)(THIS_ D3DXINCLUDE_TYPE IncludeType, LPCSTR pFileName, LPCVOID pParentData, LPCVOID *ppData, UINT *pBytes) ;
	STDMETHOD(Close)(THIS_ LPCVOID pData) ;
};