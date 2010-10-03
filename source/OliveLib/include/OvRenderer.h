#pragma once
#include "OvUtility.h"
#include "OvMemObject.h"
#include "OvAutoPtr.h"
#include "OvRefBase.h"
#include "OvSingleton.h"
#include "OvRenderingCommon.h"

OvREF_POINTER(OvPixelShader);
OvREF_POINTER(OvVertexShader);
OvREF_POINTER(OvTexture);
OvREF_POINTER(OvCubeTexture);

class OvRenderer : public OvSingletonBase< OvRenderer >
{
	OvRTTI_DECL_ROOT(OvRenderer);
public:

	OvRenderer();
	~OvRenderer();

	bool			GenerateRenderer();

	LPDIRECT3DSURFACE9 ChangeRenderTarget( unsigned targetIndex, LPDIRECT3DSURFACE9 renderTarget );
	LPDIRECT3DSURFACE9 ChangeDepthStencil( LPDIRECT3DSURFACE9 depthStencil );

	bool			ClearTarget();
	bool			BeginTarget();
	bool			EndTarget();
	bool			PresentTarget();

	void			SetPixelShader( OvPixelShaderSPtr shader );
	void			SetVertexShader( OvVertexShaderSPtr shader );
	bool			SetTexture(UINT uiSamplerIndex,OvTextureSPtr pTexture);
	bool			SetCubeTexture(UINT uiSamplerIndex,OvCubeTextureSPtr pTexture);

	void			SetVertexStream( WORD streamIndex, const SVertexStreamInfo& streamInfo );
	void			SetIndexStream( LPDIRECT3DINDEXBUFFER9 streamBuffer );
	void			SetVertexDeclaration( LPDIRECT3DVERTEXDECLARATION9 decl );
	bool			DrawPrimitive( D3DPRIMITIVETYPE primitiveType, size_t primCount );

	void			RenderUnitRect();

//////////////////////////////////////////////////////////////////////////

	LPDIRECT3DVERTEXBUFFER9 CreateVertexStream( void* buffer, size_t stride, size_t count );
	LPDIRECT3DINDEXBUFFER9	CreateIndexStream( void* buffer, size_t stride, size_t count);
	LPDIRECT3DVERTEXDECLARATION9 CreateVertexDeclaration( D3DVERTEXELEMENT9* vertElement );

	LPDIRECT3DDEVICE9	GetDevice();

private:

	LPDIRECT3DDEVICE9			m_device;

};


