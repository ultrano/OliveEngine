#pragma once
#include "OvUtility.h"
#include "OvMemObject.h"
#include "OvAutoPtr.h"
#include "OvRefBase.h"
#include "OvSingleton.h"
#include "OvDevice.h"
#include "OvColor.h"

OvREF_POINTER(OvPixelShader);
OvREF_POINTER(OvVertexShader);
OvREF_POINTER(OvTexture);
OvREF_POINTER(OvCubeTexture);
class OvRenderer : public OvSingletonBase< OvRenderer >
{
	friend class OliveDevice;
	OvRTTI_DECL_ROOT(OvRenderer);
public:

	OvRenderer();
	~OvRenderer();

	bool SetRenderTarget( OvTextureSPtr render_texture, bool clear_buffer = true, bool clear_zbuffer = true, const OvColor& color = OvColor(255,0,0,0) );
	LPDIRECT3DSURFACE9 SetDepthStencil( LPDIRECT3DSURFACE9 depthStencil );

	bool			BeginTarget(bool clear_buffer = true, bool clear_zbuffer = true, const OvColor& color = OvColor(255,0,0,0) );
	bool			EndTarget();
	bool			PresentTarget();

	bool			SetSamplerState( DWORD sampler, DWORD type, DWORD value );

	void			SetPixelShader( OvPixelShaderSPtr shader );
	void			SetVertexShader( OvVertexShaderSPtr shader );
	bool			SetTexture(UINT uiSamplerIndex,OvTextureSPtr pTexture);
	bool			SetCubeTexture(UINT uiSamplerIndex,OvCubeTextureSPtr pTexture);

	void			SetVertexStream( WORD streamIndex, const SVertexStreamInfo& streamInfo );
	void			SetIndexStream( LPDIRECT3DINDEXBUFFER9 streamBuffer );
	void			SetVertexDeclaration( LPDIRECT3DVERTEXDECLARATION9 decl );
	bool			DrawPrimitive( D3DPRIMITIVETYPE primitiveType, UINT primCount );

	void			RenderUnitRect( OvVertexShaderSPtr v_shader = NULL , OvPixelShaderSPtr p_shader = NULL );

	//////////////////////////////////////////////////////////////////////////

	LPDIRECT3DVERTEXBUFFER9 CreateVertexStream( void* buffer, UINT stride, UINT count );
	LPDIRECT3DINDEXBUFFER9	CreateIndexStream( void* buffer, UINT stride, UINT count);
	LPDIRECT3DVERTEXDECLARATION9 CreateVertexDeclaration( D3DVERTEXELEMENT9* vertElement );

	//////////////////////////////////////////////////////////////////////////

	OvTextureSPtr CreateRenderTexture( unsigned width, unsigned height, unsigned level = 1, D3DFORMAT format = D3DFMT_A8B8G8R8 );
	OvTextureSPtr CreateDepthStencilTexture( unsigned width, unsigned height, unsigned level, D3DFORMAT format );
	OvCubeTextureSPtr CreateRenderCubeTexture( unsigned size, unsigned level, D3DFORMAT format );

	//////////////////////////////////////////////////////////////////////////
	OvDevice		GetDevice();
	HWND			GetWindowHandle();

private:

	bool			_generate_renderer();

private:

	LPDIRECT3DDEVICE9			m_device;
	LPDIRECT3DSURFACE9			m_default_display_buffer;
	CRITICAL_SECTION			m_device_occupy;
	HWND						m_window_handle;

};