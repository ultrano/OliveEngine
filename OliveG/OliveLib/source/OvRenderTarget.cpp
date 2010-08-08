#include "OvRenderTarget.h"
#include "OvRenderer.h"
#include "OvTexture.h"
#include "OvSurface.h"
#include <d3dx9.h>

struct OvRenderTarget::OvPimple : OvMemObject
{
	OvTextureSPtr	mTargetTexture;
	OvSurfaceSPtr		m_pDepthStencilSurface;
	bool			m_bIsTargetLocked;
	LPDIRECT3DSURFACE9				m_pOldRenderTarget;
	LPDIRECT3DSURFACE9				m_pOldDSBuffer;
};

OvRenderTarget::OvRenderTarget()
:m_pPimple(OvNew OvRenderTarget::OvPimple)
{
	m_pPimple->m_bIsTargetLocked = false;
	m_pPimple->mTargetTexture	=	NULL;
	m_pPimple->m_pDepthStencilSurface	=	NULL;
	m_pPimple->m_pOldRenderTarget	=	NULL;
	m_pPimple->m_pOldDSBuffer	=	NULL;


}

OvRenderTarget::~OvRenderTarget()
{
	m_pPimple->mTargetTexture = NULL;
}
void	OvRenderTarget::SetRenderTexture(OvTextureSPtr pTexture)
{
	if ( OvRTTI_Util::IsKindOf< OvTexture >( pTexture ) )
	{
		m_pPimple->mTargetTexture = pTexture;
	}
}

OvTextureSPtr OvRenderTarget::GetRenderTexture()
{
	return m_pPimple->mTargetTexture;
}

void	OvRenderTarget::SetDepthStencilSurface(OvSurfaceSPtr pSurface)
{
	m_pPimple->m_pDepthStencilSurface = pSurface;
}
OvSurfaceSPtr OvRenderTarget::GetDepthStencilSurface()
{
	return m_pPimple->m_pDepthStencilSurface;
}

void	OvRenderTarget::LockTarget()
{
	if (IsTargetLocked() == false)
	{
		m_pPimple->m_bIsTargetLocked = true;
		LPDIRECT3DDEVICE9	kpDevice = OvRenderer::GetInstance()->GetDevice();
		LPDIRECT3DTEXTURE9	kpTexture	=	NULL;
		if (kpDevice)
		{
			LPDIRECT3DSURFACE9	kpNewSurface = NULL;
			if (GetRenderTexture())
			{
				kpNewSurface = NULL;

				kpTexture	=	GetRenderTexture()->ToDxTexture();
				kpDevice->GetRenderTarget(0,&m_pPimple->m_pOldRenderTarget);
				kpTexture->GetSurfaceLevel(0,&kpNewSurface);
				kpDevice->SetRenderTarget(0,kpNewSurface);
			}

			if (GetDepthStencilSurface())
			{
				kpNewSurface = NULL;

				kpNewSurface = (LPDIRECT3DSURFACE9)GetDepthStencilSurface()->GetSurface();
				kpDevice->GetDepthStencilSurface(&m_pPimple->m_pOldDSBuffer);
				kpDevice->SetDepthStencilSurface(kpNewSurface);
			}
		}
	}
}
void	OvRenderTarget::UnlockTarget()
{
	if (IsTargetLocked())
	{
		LPDIRECT3DDEVICE9	kpDevice = OvRenderer::GetInstance()->GetDevice();
		m_pPimple->m_bIsTargetLocked = false;
		if (m_pPimple->m_pOldRenderTarget)
		{
			kpDevice->SetRenderTarget(0,m_pPimple->m_pOldRenderTarget);
			m_pPimple->m_pOldRenderTarget->Release();
		}
		if (m_pPimple->m_pOldDSBuffer)
		{
			kpDevice->SetDepthStencilSurface(m_pPimple->m_pOldDSBuffer);
			m_pPimple->m_pOldDSBuffer->Release();
		}
		m_pPimple->m_pOldRenderTarget	=	NULL;
		m_pPimple->m_pOldDSBuffer	=	NULL;
	}
}
bool	OvRenderTarget::IsTargetLocked()
{
	return m_pPimple->m_bIsTargetLocked;
}