#include "OvRenderer.h"

#include <d3dx9.h>
#include "OvTexture.h"
#include "OvTexture.h"
#include "OvSurface.h"
#include "OvCamera.h"
#include <queue>
#include <map>
#include <vector>

#include "OvMatrix.h"
//! Temporary include
#include "OvUtility.h"
#include "OvStringUtility.h"
//


bool	SafeCopyToVertexBuffer(LPDIRECT3DVERTEXBUFFER9 pVertexBuffer, size_t stVertStreamSize, void* pVertStreamPointer)
{

	if (pVertStreamPointer && pVertexBuffer)
	{
		void*	kpLockedBuffer = NULL;
		if (stVertStreamSize && SUCCEEDED(pVertexBuffer->Lock(0,stVertStreamSize,(void**)&kpLockedBuffer,0)))
		{
			memcpy(kpLockedBuffer,pVertStreamPointer,stVertStreamSize);
			pVertexBuffer->Unlock();
			return true;
		}
		else
		{
			OvAssertMsg("Locking VertexBuffer is failed");
		}
	}
	return false;
}
bool	SafeCopyToIndexBuffer(LPDIRECT3DINDEXBUFFER9 pIndexBuffer, size_t stFaceStreamSize, void* pFaceStreamPointer)
{
	if (pFaceStreamPointer && pIndexBuffer)
	{
		void*	kpLockedBuffer = NULL;
		if (stFaceStreamSize && SUCCEEDED(pIndexBuffer->Lock(0,stFaceStreamSize,(VOID**)&kpLockedBuffer,0)))
		{
			memcpy(kpLockedBuffer,pFaceStreamPointer,stFaceStreamSize);
			pIndexBuffer->Unlock();
			return true;
		}
		else
		{
			OvAssertMsg("Locking IndexBuffer is failed");
		}
	}
	return false;
}

OvRTTI_IMPL_ROOT(OvRenderer);
OvSingletonEx_IMPL(OvRenderer);

struct OvRenderer::OvPimple : OvMemObject
{
	LPDIRECT3DDEVICE9			mpDirect3DDevice;
	LPDIRECT3DVERTEXBUFFER9		mpVertexBuffer	;
	LPDIRECT3DINDEXBUFFER9		mpIndexBuffer	;
	DWORD						mdMaxVertexBufferSize;
	DWORD						mdMaxIndexBufferSize;
	HWND						mhWindowHandle;
	DWORD						mdWindowHeight;
	DWORD						mdWindowWidth;


	OvMatrix					mSelectedViewMatrix;
	OvMatrix					mSelectedProjectMatrix;


};

void	OvRenderer::Singleton_InitializeProcessing()
{
	m_pPimple = OvNew OvRenderer::OvPimple;
	m_pPimple->mpDirect3DDevice			=	NULL;
	m_pPimple->mpVertexBuffer			=	NULL;
	m_pPimple->mpIndexBuffer			=	NULL;
	m_pPimple->mdMaxVertexBufferSize	=	0;
	m_pPimple->mdMaxIndexBufferSize		=	0;
	m_pPimple->mhWindowHandle			=	NULL;
	m_pPimple->mdWindowHeight			=	0;
	m_pPimple->mdWindowWidth			=	0;
}
void	OvRenderer::Singleton_TerminateProcessing()
{
	LPDIRECT3DINDEXBUFFER9&		kpIndexBuffer	=	m_pPimple->mpIndexBuffer;
	if (NULL != kpIndexBuffer )
	{
		kpIndexBuffer->Release();
	}
	LPDIRECT3DVERTEXBUFFER9&		kpVertexBuffer	=	m_pPimple->mpVertexBuffer;
	if (NULL != kpVertexBuffer )
	{
		kpVertexBuffer->Release();
	}
	LPDIRECT3DDEVICE9	kpDX9Device = m_pPimple->mpDirect3DDevice;
	if (kpDX9Device)
	{
		kpDX9Device->Release();
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

bool		OvRenderer::GenerateRenderer(HWND _hTargetWindowHangle)
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
		&(m_pPimple->mpDirect3DDevice)
		);

	LPDIRECT3DDEVICE9 kpDevice = m_pPimple->mpDirect3DDevice;

	m_pPimple->mhWindowHandle = _hTargetWindowHangle;

	WINDOWINFO	kWndInfo ;
	GetWindowInfo(m_pPimple->mhWindowHandle,&kWndInfo);
	m_pPimple->mdWindowHeight = kWndInfo.rcWindow.bottom - kWndInfo.rcWindow.top;
	m_pPimple->mdWindowWidth  = kWndInfo.rcWindow.right - kWndInfo.rcWindow.left;

	kpDevice->SetRenderState(D3DRS_ZENABLE,TRUE);


// 	kpDevice->SetRenderState(D3DRS_ALPHABLENDENABLE,true);
// 	kpDevice->SetRenderState(D3DRS_SRCBLEND,D3DBLEND_ONE);
// 	kpDevice->SetRenderState(D3DRS_DESTBLEND,D3DBLEND_ONE);
// 	kpDevice->SetRenderState(D3DRS_BLENDOP,D3DBLENDOP_ADD);
// 
// 	kpDevice->SetRenderState(D3DRS_SRCBLENDALPHA,D3DBLEND_ZERO);
// 	kpDevice->SetRenderState(D3DRS_DESTBLENDALPHA,D3DBLEND_ZERO);
// 	kpDevice->SetRenderState(D3DRS_BLENDOPALPHA,D3DBLENDOP_ADD);

	kpDevice->SetRenderState(D3DRS_CULLMODE,D3DCULL_CCW);
	kpDevice->SetRenderState(D3DRS_LIGHTING,false);


	/*OvMatrix	kMatProjeTexOffset;
	kMatProjeTexOffset = kMatProjeTexOffset * OvMatrix().Scale(0.5f,-0.5f,1);
	kMatProjeTexOffset = kMatProjeTexOffset * OvMatrix().Translate(0.5f,0.5f,0);*/

	return SUCCEEDED(hr);

};



/*void			OvRenderer::DrawMesh(OvMeshSPtr pMesh)
{
	if (pMesh && OvRTTI_Util::IsKindOf< OvMesh >( pMesh ))
	{

		LPDIRECT3DDEVICE9				kpDX9Device		= m_pPimple->mpDirect3DDevice;

		LPDIRECT3DVERTEXBUFFER9&		kpVertexBuffer	=	m_pPimple->mpVertexBuffer;
		LPDIRECT3DINDEXBUFFER9&			kpIndexBuffer	=	m_pPimple->mpIndexBuffer;

		SafeCopyToVertexBuffer(kpVertexBuffer, pMesh->GetVertexStreamByteSize(), pMesh->GetVertexStreamRealPointer());
		SafeCopyToIndexBuffer(kpIndexBuffer, pMesh->GetIndexedFaceStreamByteSize(), pMesh->GetIndexedFaceStreamRealPointer());

		kpDX9Device->SetStreamSource(0,kpVertexBuffer,0,pMesh->GetVertexStrideByteSize());
		kpDX9Device->SetIndices(kpIndexBuffer);
		kpDX9Device->SetFVF(pMesh->GetVertexFormatFlag());

		HRESULT kHs = -1;
		switch (pMesh->GetPrimitiveType())
		{
		case OvNSMeshDescription::ePrimitiveType_None_Indexed :
			kHs = kpDX9Device->DrawPrimitive((D3DPRIMITIVETYPE)pMesh->GetDrawType(),0,pMesh->GetVertexCount());
			break;
		case OvNSMeshDescription::ePrimitiveType_Indexed : 
			kHs = kpDX9Device->DrawIndexedPrimitive(
				(D3DPRIMITIVETYPE)pMesh->GetDrawType()
				,0
				,0
				,pMesh->GetVertexCount()
				,0
				,pMesh->GetFaceCount() 
				);
			break;
		}
		if (FAILED(kHs))
		{
			OvAssertMsg("Draw Failed");
		}
	}
}*/
bool			OvRenderer::ClearTarget()
{
	LPDIRECT3DDEVICE9	kpDX9Device = m_pPimple->mpDirect3DDevice;

	if (FAILED(kpDX9Device->Clear(0,
		NULL,
		D3DCLEAR_TARGET | D3DCLEAR_ZBUFFER ,
		D3DCOLOR_XRGB(1,1,1),
		1.0f,
		0)))
	{
		OvAssertMsg("Failed Clear RenderTarget");
	}

	return true;
}

bool			OvRenderer::BeginTarget()
{
	LPDIRECT3DDEVICE9	kpDX9Device = m_pPimple->mpDirect3DDevice;

	if (FAILED(kpDX9Device->BeginScene()))
	{
		OvAssertMsg("Failed Begin RenderTarget");
	}
	;

	return true;
}

bool			OvRenderer::EndTarget()
{
	LPDIRECT3DDEVICE9	kpDX9Device = m_pPimple->mpDirect3DDevice;

	if (FAILED(kpDX9Device->EndScene()))
	{
		OvAssertMsg("Failed End RenderTarget");
	}

	return true;
}

bool			OvRenderer::PresentTarget()
{
	LPDIRECT3DDEVICE9	kpDX9Device = m_pPimple->mpDirect3DDevice;

	if (FAILED(kpDX9Device->Present(0,0,0,0)))
	{
		OvAssertMsg("Failed Present RenderTarget");
	}

	return true;
}
bool	OvRenderer::ExtentionVertexBuffer(DWORD dBufferSize)
{
	LPDIRECT3DDEVICE9	kpDX9Device =	m_pPimple->mpDirect3DDevice;

	//! Extention VertexBuffer
	if (dBufferSize > m_pPimple->mdMaxVertexBufferSize)
	{
		LPDIRECT3DVERTEXBUFFER9&		kpVertexBuffer	=	m_pPimple->mpVertexBuffer;
		if (NULL != kpVertexBuffer )
		{
			kpVertexBuffer->Release();
		}
		if (FAILED(kpDX9Device->CreateVertexBuffer(dBufferSize,0,0,D3DPOOL_MANAGED,&kpVertexBuffer,NULL)))
		{
			OvAssertMsg("Creating VertexBuffer is failed");
			return false;
		}
		m_pPimple->mdMaxVertexBufferSize	=	dBufferSize;
	}
	else
	{
		return false;
	}
	return true;

}
bool	OvRenderer::ExtentionIndexBuffer(DWORD dBufferSize)
{
	LPDIRECT3DDEVICE9	kpDX9Device =	m_pPimple->mpDirect3DDevice;

	//! Extention VertexBuffer
	if (dBufferSize > m_pPimple->mdMaxIndexBufferSize)
	{
		LPDIRECT3DINDEXBUFFER9&		kpIndexBuffer	=	m_pPimple->mpIndexBuffer;
		if (NULL != kpIndexBuffer )
		{
			kpIndexBuffer->Release();
		}
		if (FAILED(kpDX9Device->CreateIndexBuffer(dBufferSize,0,D3DFMT_INDEX16,D3DPOOL_MANAGED,&kpIndexBuffer,NULL)))
		{
			OvAssertMsg("Creating VertexBuffer is failed");
			return false;
		}
		m_pPimple->mdMaxIndexBufferSize	=	dBufferSize;
	}
	else
	{
		return false;
	}
	return true;

}

OvTextureSPtr	OvRenderer::LoadTexture(const char* pFile)
{
	if (pFile)
	{
		LPDIRECT3DDEVICE9 kpDevice = (LPDIRECT3DDEVICE9)GetDevice();
		if (kpDevice)
		{
			LPDIRECT3DTEXTURE9	kpTexture = NULL;
			if (SUCCEEDED(D3DXCreateTextureFromFile(kpDevice,pFile,&kpTexture)) )
			{
				OvTextureSPtr	kpDiffTex = new OvTexture(kpTexture);
				return kpDiffTex;
			}
		}
	}
	return NULL;
}

OvTextureSPtr	OvRenderer::CreateTexture(size_t stWidth,size_t stHeight,size_t stMipLevel,DWORD dUsage,DWORD dFormat)
{
	LPDIRECT3DDEVICE9 kpDevice = (LPDIRECT3DDEVICE9)GetDevice();

	LPDIRECT3DTEXTURE9 kpTexture = NULL;

	if (kpDevice)
	{
		if (SUCCEEDED(D3DXCreateTexture(
			kpDevice
			,stWidth
			,stHeight
			,stMipLevel
			,dUsage
			,(D3DFORMAT)dFormat
			,D3DPOOL_DEFAULT
			,&(kpTexture)
			)))
		{
			OvTextureSPtr	kpRenderTex = new OvTexture((void*)kpTexture);
			return kpRenderTex;
		}
	}
	return NULL;

}
OvSurfaceSPtr	OvRenderer::CreateDepthStencilSurface(size_t stWidth,size_t stHeight,DWORD dFormat,DWORD dMultiSample,DWORD dMultiSampleQuality,bool bIdDiscard)
{

	LPDIRECT3DDEVICE9 kpDevice = (LPDIRECT3DDEVICE9)GetDevice();
	if (kpDevice )
	{
		LPDIRECT3DSURFACE9	kpBuffer = NULL;
		kpDevice->CreateDepthStencilSurface(
			stWidth, stHeight, 
			(D3DFORMAT)dFormat, (D3DMULTISAMPLE_TYPE)dMultiSample, dMultiSampleQuality,
			bIdDiscard, &kpBuffer , NULL);

		OvSurfaceSPtr	kpSurface = OvNew OvSurface((void*)kpBuffer);

		return kpSurface;
	}

	return NULL;

}
void*	OvRenderer::GetDevice()
{
	LPDIRECT3DDEVICE9	kpDX9Device =	m_pPimple->mpDirect3DDevice;
	return (void*)kpDX9Device;
}

DWORD	OvRenderer::GetRenderWindowHeight()
{
	return m_pPimple->mdWindowHeight;
}

DWORD	OvRenderer::GetRenderWindowWidth()
{
	return m_pPimple->mdWindowWidth;
}
