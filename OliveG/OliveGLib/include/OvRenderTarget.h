#pragma once

#include "OvRefBase.h"
#include "OvAutoPtr.h"

OvREF_POINTER(OvTexture);
OvREF_POINTER(OvSurface);
OvREF_POINTER(OvRenderTarget);

class OvRenderTarget : public OvRefBase
{
public:

	OvRenderTarget();
	~OvRenderTarget();

	void	SetRenderTexture(OvTextureSPtr pTexture);
	OvTextureSPtr GetRenderTexture();

	void	SetDepthStencilSurface(OvSurfaceSPtr pSurface);
	OvSurfaceSPtr GetDepthStencilSurface();

	void	LockTarget();
	void	UnlockTarget();

	bool	IsTargetLocked();

private:
	struct OvPimple;
	OvAutoPtr< OvPimple> m_pPimple;
};