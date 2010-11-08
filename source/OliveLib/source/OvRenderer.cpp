#include "OvRenderer.h"
#include "OvMessageManager.h"

#include <d3dx9.h>
#include "OvTexture.h"
#include "OvVertexShader.h"
#include "OvPixelShader.h"

#include "OvCamera.h"
#include <queue>
#include <map>
#include <vector>

#include "OvMatrix.h"
//! Temporary include
#include "OvUtility.h"
#include "OvStringUtility.h"

OvRTTI_IMPL_ROOT(OvRenderer);



OvRenderer::OvRenderer()
:m_device( NULL )
{
	::InitializeCriticalSection( &m_device_occupy );
}
OvRenderer::~OvRenderer()
{
	OvDevice device = GetDevice();
	if ( device )
	{
		device->Release();
	}
	::DeleteCriticalSection( &m_device_occupy );
}


struct OvDirect3D9ObjectSafeRelease
{
	OvDirect3D9ObjectSafeRelease(LPDIRECT3D9 _pDirect3D9Object):
m_pDirect3D9Object(NULL)
{
	m_pDirect3D9Object = _pDirect3D9Object;
}
~OvDirect3D9ObjectSafeRelease()
{
	if (m_pDirect3D9Object )
		m_pDirect3D9Object->Release();
}
LPDIRECT3D9 m_pDirect3D9Object;
};

bool		OvRenderer::GenerateRenderer()
{

	LPDIRECT3D9 kpDirect3D9Object = Direct3DCreate9(D3D_SDK_VERSION);

	if (!kpDirect3D9Object)
	{
		OvAssertMsg("Direct3DCreate9() is Failed");
		return false;
	}

	/*D3DCAPS9 kCapability;
	kpDirect3D9Object->GetDeviceCaps(D3DADAPTER_DEFAULT,D3DDEVTYPE_HAL,&kCapability);
	OvMessageBox(OvFormatString("랜더 타겟 한계 개수: %d",kCapability.NumSimultaneousRTs),"MRT Limit Count");*/

	char windowClassName[] = "Olive_Renderer_View";

	WNDCLASS WndClass;

	WndClass.cbClsExtra		=	0;
	WndClass.cbWndExtra		=	0;
	WndClass.hbrBackground	=	(HBRUSH)GetStockObject(WHITE_BRUSH);
	WndClass.hCursor		=	LoadCursor(NULL,IDC_ARROW);
	WndClass.hIcon			=	LoadIcon(NULL,IDI_APPLICATION);
	WndClass.hInstance		=	GetModuleHandle(NULL);
	WndClass.lpfnWndProc	=	(WNDPROC)OvWinMsgManager::ListenMessage;
	WndClass.lpszClassName	=	windowClassName;
	WndClass.lpszMenuName	=	NULL;
	WndClass.style			=	CS_HREDRAW | CS_VREDRAW | CS_DBLCLKS ;

	RegisterClass(&WndClass);

	HWND _hTargetWindowHangle = CreateWindow
		( windowClassName
		, windowClassName
		, WS_OVERLAPPEDWINDOW | WS_VISIBLE
		, 300, 50
		, 800, 600
		, NULL
		, NULL
		, GetModuleHandle(NULL)
		, NULL);

	OvDirect3D9ObjectSafeRelease kSafeRelease(kpDirect3D9Object);

	D3DPRESENT_PARAMETERS	d3dpp;
	ZeroMemory(&d3dpp,sizeof(d3dpp));

	d3dpp.Windowed					=	TRUE;
	d3dpp.BackBufferFormat			=	D3DFMT_UNKNOWN;
	d3dpp.SwapEffect				=	D3DSWAPEFFECT_DISCARD;
	d3dpp.EnableAutoDepthStencil	=	TRUE;
	d3dpp.AutoDepthStencilFormat	=	D3DFMT_D16;


	HRESULT hr = kpDirect3D9Object->CreateDevice(
		D3DADAPTER_DEFAULT,
		D3DDEVTYPE_HAL,
		_hTargetWindowHangle,
		D3DCREATE_SOFTWARE_VERTEXPROCESSING,
		&d3dpp,
		&(m_device)
		);
	OvDevice device = GetDevice();
	//m_device->SetRenderState(D3DRS_ZENABLE,TRUE);

	// 	m_device->SetSamplerState( 1, D3DSAMP_MINFILTER, D3DTEXF_LINEAR );
	// 	m_device->SetSamplerState( 1, D3DSAMP_MAGFILTER, D3DTEXF_LINEAR );
	 	device->SetRenderState(D3DRS_CULLMODE,D3DCULL_NONE);
	//m_device->SetRenderState(D3DRS_LIGHTING,false);

	return SUCCEEDED(hr);

};

LPDIRECT3DSURFACE9 OvRenderer::ChangeRenderTarget( unsigned targetIndex, LPDIRECT3DSURFACE9 renderTarget )
{
	if ( OvDevice device = GetDevice() )
	{
		LPDIRECT3DSURFACE9 oldRenderTarget = NULL;
		HRESULT hr0 = device->GetRenderTarget( targetIndex, &oldRenderTarget );
		HRESULT hr1 = device->SetRenderTarget( targetIndex, renderTarget );
		if ( SUCCEEDED( hr0 ) && SUCCEEDED( hr1 ) )
		{
			return oldRenderTarget;
		}
	}
	return NULL;
}

LPDIRECT3DSURFACE9 OvRenderer::ChangeDepthStencil( LPDIRECT3DSURFACE9 depthStencil )
{
	if ( OvDevice device = GetDevice() )
	{
		LPDIRECT3DSURFACE9 oldDepthStencil = NULL;
		HRESULT hr0 = device->GetDepthStencilSurface( &oldDepthStencil );
		HRESULT hr1 = device->SetDepthStencilSurface( depthStencil );
		if ( SUCCEEDED( hr0 ) && SUCCEEDED( hr1 ) )
		{
			return oldDepthStencil;
		}
	}
	return NULL;
}
bool			OvRenderer::ClearTarget()
{
	OvDevice device = GetDevice();
	HRESULT hr = E_FAIL;
	if ( device && SUCCEEDED( hr = device->Clear(0,
		NULL,
		D3DCLEAR_TARGET | D3DCLEAR_ZBUFFER ,
		D3DCOLOR_XRGB(1,1,1),
		1.0f,
		0)))
	{
		return true;
	}
	OvAssertMsg("Failed Clear RenderTarget");
	return false;
}

bool			OvRenderer::BeginTarget()
{
	OvDevice device = GetDevice();
	HRESULT hr = E_FAIL;
	if ( device && SUCCEEDED( hr = device->BeginScene()))
	{
		return true;
	}
	OvAssertMsg("Failed Begin RenderTarget");
	return false;
}

bool			OvRenderer::EndTarget()
{
	OvDevice device = GetDevice();
	HRESULT hr = E_FAIL;
	if ( device && SUCCEEDED( hr = device->EndScene()))
	{
		return true;
	}
	OvAssertMsg("Failed End RenderTarget");
	return false;
}

bool			OvRenderer::PresentTarget()
{
	OvDevice device = GetDevice();
	HRESULT hr = E_FAIL;
	if ( device && SUCCEEDED( hr = device->Present(0,0,0,0) ))
	{
		return true;
	}

	OvAssertMsg(OvFormatString("Failed Present RenderTarget code: %d", (DWORD)hr ));
	return false;
}

bool OvRenderer::SetSamplerState( DWORD sampler, DWORD type, DWORD value )
{
	OvDevice device = GetDevice();
	HRESULT hr = E_FAIL;
	if ( device && SUCCEEDED( hr = device->SetSamplerState( sampler, (D3DSAMPLERSTATETYPE)type, value ) )  )
	{
		return true;
	}
	OvAssertMsg("Failed SetSamplerState");
	return false;
}

void OvRenderer::SetPixelShader( OvPixelShaderSPtr shader )
{
	OvDevice device = GetDevice();
	if ( device && shader )
	{
		HRESULT hr = device->SetPixelShader( shader->ToDirectShader() );
		if ( FAILED( hr ) )
		{
			OvAssertMsg("Failed SetPixelShader");
		}
	}
}

void OvRenderer::SetVertexShader( OvVertexShaderSPtr shader )
{
	OvDevice device = GetDevice();
	if ( device && shader )
	{
		HRESULT hr = device->SetVertexShader( shader->ToDirectShader() );
		if ( FAILED( hr ) )
		{
			OvAssertMsg("Failed SetVertexShader");
		}
	}
}

bool OvRenderer::SetTexture(UINT uiSamplerIndex,OvTextureSPtr pTexture)
{
	OvDevice kpDevice =  GetDevice();
	if (kpDevice && pTexture)
	{
		HRESULT kHs = E_FAIL;
		kHs = kpDevice->SetTexture( uiSamplerIndex, pTexture->ToDxTexture() );
		return SUCCEEDED(kHs);
	}
	return false;
}

bool OvRenderer::SetCubeTexture(UINT uiSamplerIndex,OvCubeTextureSPtr pTexture)
{
	OvDevice kpDevice =  GetDevice();
	if ( kpDevice && pTexture )
	{
		HRESULT kHs = E_FAIL;
		kHs = kpDevice->SetTexture( uiSamplerIndex, pTexture->ToDxCubeTexture() );
		return SUCCEEDED(kHs);
	}
	return false;
}

void OvRenderer::SetVertexStream( WORD streamIndex, const SVertexStreamInfo& streamInfo )
{
	OvDevice device = GetDevice();
	if ( device )
	{		
		LPDIRECT3DVERTEXBUFFER9 Stream = NULL;
		UINT Stride = 0;
		
		Stream = streamInfo.vertexStream;
		Stride = streamInfo.vertexStride;

		HRESULT hr = device->SetStreamSource( streamIndex, Stream, 0, Stride );
		OvAssert( SUCCEEDED( hr ) );

	}
}

void OvRenderer::SetIndexStream( LPDIRECT3DINDEXBUFFER9 streamBuffer )
{
	OvDevice device = GetDevice();
	if ( device )
	{
		HRESULT hr = device->SetIndices( streamBuffer );
		OvAssert( SUCCEEDED( hr ) );
	}
}
void OvRenderer::SetVertexDeclaration( LPDIRECT3DVERTEXDECLARATION9 decl )
{
	OvDevice device = GetDevice();
	if ( device )
	{
		HRESULT hr = device->SetVertexDeclaration( decl );
		OvAssert( SUCCEEDED( hr ) );
	}
}
bool OvRenderer::DrawPrimitive( D3DPRIMITIVETYPE primitiveType, UINT primCount )
{
	OvDevice device = GetDevice();
	if ( device )
	{
		HRESULT hr = device->DrawPrimitive
			( primitiveType
			, 0
			, primCount);
		return SUCCEEDED( hr );
	}
	return false;
}

void OvRenderer::RenderUnitRect( OvVertexShaderSPtr v_shader , OvPixelShaderSPtr p_shader )
{
	struct SScreenRect
	{
		OvPoint3 pos; OvPoint2 tex;
	};
	static D3DVERTEXELEMENT9 rect_elem[] =
	{
		{ 0, 0
		, D3DDECLTYPE_FLOAT3
		, D3DDECLMETHOD_DEFAULT
		, D3DDECLUSAGE_POSITION, 0 },

		{ 0, 12
		, D3DDECLTYPE_FLOAT2
		, D3DDECLMETHOD_DEFAULT
		, D3DDECLUSAGE_TEXCOORD, 0 },
		D3DDECL_END()
	};
	static SScreenRect rect[] = 
	{ {OvPoint3(-1,-1,0),OvPoint2(0,1)}
	, {OvPoint3(-1,+1,0),OvPoint2(0,0)}
	, {OvPoint3(+1,+1,0),OvPoint2(1,0)}
	, {OvPoint3(+1,-1,0),OvPoint2(1,1)}};

	static LPDIRECT3DVERTEXBUFFER9 rectVertBuffer = CreateVertexStream( (void*)&rect[0], sizeof( SScreenRect ), 4 );
	static LPDIRECT3DVERTEXDECLARATION9 rectDecl = CreateVertexDeclaration( rect_elem );

	if ( v_shader ) SetVertexShader( v_shader );
	if ( p_shader ) SetPixelShader( p_shader );
	SetVertexStream( 0, SVertexStreamInfo( rectVertBuffer, sizeof( SScreenRect ), 0) );
	SetVertexDeclaration( rectDecl );
	DrawPrimitive( D3DPT_TRIANGLEFAN, 2);
}

OvDevice	OvRenderer::GetDevice()
{	
	return OvDevice( m_device, m_device_occupy );
}

LPDIRECT3DVERTEXBUFFER9 OvRenderer::CreateVertexStream( void* buffer, UINT stride, UINT count )
{
	OvDevice device = GetDevice();
	if ( device )
	{
		LPDIRECT3DVERTEXBUFFER9 vertexStream = NULL;
		UINT streamSize = count * stride;
		HRESULT hr = device->CreateVertexBuffer
			( streamSize
			, 0
			, 0
			, D3DPOOL_MANAGED
			, &vertexStream
			, NULL
			);
		if ( SUCCEEDED(hr) && vertexStream )
		{
			void* copyDest = NULL;
			if ( SUCCEEDED(vertexStream->Lock( 0, streamSize, &copyDest, 0)) && copyDest)
			{
				memcpy( copyDest, buffer, streamSize );
				vertexStream->Unlock();
				return vertexStream;
			}
		}
	}
	return NULL;
}

LPDIRECT3DINDEXBUFFER9 OvRenderer::CreateIndexStream( void* buffer, UINT stride, UINT count )
{
	OvDevice device = GetDevice();
	if ( device )
	{
		LPDIRECT3DINDEXBUFFER9	streamBuffer = NULL;
		UINT streamSize = count * stride;
		HRESULT hr = device->CreateIndexBuffer
			( streamSize
			, 0
			, D3DFMT_INDEX16
			, D3DPOOL_MANAGED
			, &streamBuffer
			, NULL
			);

		if ( SUCCEEDED(hr) && streamBuffer )
		{
			void* copyDest = NULL;
			if ( SUCCEEDED(streamBuffer->Lock( 0, streamSize, &copyDest, 0)) && copyDest)
			{
				memcpy( copyDest, buffer, streamSize );
				streamBuffer->Unlock();
				return streamBuffer;
			}
		}
	}
	return NULL;

}

LPDIRECT3DVERTEXDECLARATION9 OvRenderer::CreateVertexDeclaration( D3DVERTEXELEMENT9* vertElement )
{
	OvDevice device = GetDevice();
	if ( device)
	{
		LPDIRECT3DVERTEXDECLARATION9 vertDecl = NULL;
		HRESULT hr = device->CreateVertexDeclaration( vertElement, &vertDecl );
		if ( SUCCEEDED( hr ) )
		{
			return vertDecl;
		}
	}
	return NULL;
}
