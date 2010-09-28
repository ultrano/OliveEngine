#pragma once
#include "OvTexture.h"

OvREF_POINTER( OvRenderTarget );
class OvRenderTarget : public OvTexture
{
	OvRTTI_DECL( OvRenderTarget );

public:

	OvRenderTarget( LPDIRECT3DTEXTURE9 texture, LPDIRECT3DSURFACE9 depth = NULL );
	~OvRenderTarget();

	bool Lock( unsigned targetIndex = 0);
	bool Unlock();

private:

	unsigned m_reservedTargetIndex;

	LPDIRECT3DSURFACE9 m_oldTargetSurface;

	LPDIRECT3DSURFACE9 m_newDepthSurface;
	LPDIRECT3DSURFACE9 m_oldDepthSurface;

};
OvRenderTargetSPtr CreateRenderTexture( unsigned width, unsigned height, unsigned level, D3DFORMAT format );