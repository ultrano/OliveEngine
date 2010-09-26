#include "OvRenderer.h"
#include "OvMessageManager.h"

#include <d3dx9.h>
#include "OvTexture.h"
#include "OvVertexShader.h"
#include "OvPixelShader.h"

#include "OvSurface.h"
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
}
OvRenderer::~OvRenderer()
{
	
	if (m_device)
	{
		m_device->Release();
	}
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
	WndClass.lpfnWndProc	=	(WNDPROC)OvMessageManager::ListenMessage;
	WndClass.lpszClassName	=	windowClassName;
	WndClass.lpszMenuName	=	NULL;
	WndClass.style			=	CS_HREDRAW | CS_VREDRAW;

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

	//m_device->SetRenderState(D3DRS_ZENABLE,TRUE);

	// 	m_device->SetSamplerState( 1, D3DSAMP_MINFILTER, D3DTEXF_LINEAR );
	// 	m_device->SetSamplerState( 1, D3DSAMP_MAGFILTER, D3DTEXF_LINEAR );
	// 	m_device->SetRenderState(D3DRS_CULLMODE,D3DCULL_CW);
	//m_device->SetRenderState(D3DRS_LIGHTING,false);

	return SUCCEEDED(hr);

};
bool			OvRenderer::ClearTarget()
{

	if (FAILED(m_device->Clear(0,
		NULL,
		D3DCLEAR_TARGET | D3DCLEAR_ZBUFFER ,
		D3DCOLOR_XRGB(1,1,1),
		1.0f,
		0)))
	{
		OvAssertMsg("Failed Clear RenderTarget");
		return false;
	}

	return true;
}

bool			OvRenderer::BeginTarget()
{

	if (FAILED(m_device->BeginScene()))
	{
		OvAssertMsg("Failed Begin RenderTarget");
		return false;
	}

	return true;
}

bool			OvRenderer::EndTarget()
{

	if (FAILED(m_device->EndScene()))
	{
		OvAssertMsg("Failed End RenderTarget");
		return false;
	}

	return true;
}

bool			OvRenderer::PresentTarget()
{
	if (FAILED(m_device->Present(0,0,0,0)))
	{
		OvAssertMsg("Failed Present RenderTarget");
		return false;
	}

	return true;
}

void OvRenderer::SetPixelShader( OvPixelShaderSPtr shader )
{
	if ( m_device && shader )
	{
		m_device->SetPixelShader( shader->ToDirectShader() );
	}
}

void OvRenderer::SetVertexShader( OvVertexShaderSPtr shader )
{
	if ( m_device && shader )
	{
		m_device->SetVertexShader( shader->ToDirectShader() );
	}
}

void OvRenderer::SetVertexStream( WORD streamIndex, SVertexStreamInfo* streamInfo )
{
	if ( m_device )
	{		
		LPDIRECT3DVERTEXBUFFER9 Stream = NULL;
		size_t Stride = 0;
		
		if (streamInfo)
		{
			Stream = streamInfo->vertexStream;
			Stride = streamInfo->vertexStride;
		}

		HRESULT hr = m_device->SetStreamSource( streamIndex, Stream, 0, Stride );
		OvAssert( SUCCEEDED( hr ) );

	}
}

void OvRenderer::SetIndexStream( LPDIRECT3DINDEXBUFFER9 streamBuffer )
{
	if ( m_device )
	{
		HRESULT hr = m_device->SetIndices( streamBuffer );
		OvAssert( SUCCEEDED( hr ) );
	}
}
void OvRenderer::SetVertexDeclaration( LPDIRECT3DVERTEXDECLARATION9 decl )
{
	if ( m_device )
	{
		HRESULT hr = m_device->SetVertexDeclaration( decl );
		OvAssert( SUCCEEDED( hr ) );
	}
}
bool OvRenderer::DrawPrimitive( D3DPRIMITIVETYPE primitiveType, size_t primCount )
{
	if ( m_device )
	{
		HRESULT hr = m_device->DrawPrimitive
			( primitiveType
			, 0
			, primCount);
		return SUCCEEDED( hr );
	}
	return false;
}

LPDIRECT3DDEVICE9	OvRenderer::GetDevice()
{	
	return m_device;
}

LPDIRECT3DVERTEXBUFFER9 OvRenderer::CreateVertexStream( void* buffer, size_t stride, size_t count )
{
	if ( m_device )
	{
		LPDIRECT3DVERTEXBUFFER9 vertexStream = NULL;
		size_t streamSize = count * stride;
		HRESULT hr = m_device->CreateVertexBuffer
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

LPDIRECT3DINDEXBUFFER9 OvRenderer::CreateIndexStream( void* buffer, size_t stride, size_t count )
{
	if ( m_device )
	{
		LPDIRECT3DINDEXBUFFER9	streamBuffer = NULL;
		size_t streamSize = count * stride;
		HRESULT hr = m_device->CreateIndexBuffer
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
	if ( m_device )
	{
		LPDIRECT3DVERTEXDECLARATION9 vertDecl = NULL;
		HRESULT hr = m_device->CreateVertexDeclaration( vertElement, &vertDecl );
		if ( SUCCEEDED( hr ) )
		{
			return vertDecl;
		}
	}
	return NULL;
}