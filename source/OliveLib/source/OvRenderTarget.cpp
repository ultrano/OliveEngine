#include "OvRenderTarget.h"
#include "OvRenderer.h"

OvRTTI_IMPL( OvRenderTarget );

OvRenderTarget::OvRenderTarget( LPDIRECT3DTEXTURE9 texture, LPDIRECT3DSURFACE9 depth )
: OvTexture( texture )
, m_reservedTargetIndex( -1 )
, m_oldTargetSurface( NULL )
, m_newDepthSurface( depth )
, m_oldDepthSurface( NULL )
{

}

OvRenderTarget::~OvRenderTarget()
{

}
bool OvRenderTarget::Lock( unsigned targetIndex /*= 0*/ )
{
	LPDIRECT3DDEVICE9 device = OvRenderer::GetInstance()->GetDevice();
	if ( device )
	{
		if ( LPDIRECT3DSURFACE9 newTargetSurface = GetSurface() )
		{
			HRESULT hr0 = device->GetRenderTarget( targetIndex, &m_oldTargetSurface );
			HRESULT hr1 = device->SetRenderTarget( targetIndex, newTargetSurface );
			if ( SUCCEEDED( hr0 ) && SUCCEEDED( hr1 ) )
			{
				m_reservedTargetIndex = targetIndex;
				return true;
			}
		}
	}
	return false;
}

bool OvRenderTarget::Unlock()
{
	if ( m_reservedTargetIndex != -1 )
	{
		LPDIRECT3DDEVICE9 device = OvRenderer::GetInstance()->GetDevice();
		if ( device && m_oldTargetSurface )
		{
			if ( SUCCEEDED( device->SetRenderTarget( m_reservedTargetIndex, m_oldTargetSurface ) ) )
			{
				m_oldTargetSurface->Release();
				m_oldTargetSurface = NULL;
				m_reservedTargetIndex = -1;
				return true;
			}
		}
	}
	return false;
}
//////////////////////////////////////////////////////////////////////////
//////////////////////////////////////////////////////////////////////////
//////////////////////////////////////////////////////////////////////////


OvRenderTargetSPtr CreateRenderTexture( unsigned width, unsigned height, unsigned level, D3DFORMAT format )
{
	OvTextureSPtr return_texture = NULL;
	LPDIRECT3DDEVICE9 device = OvRenderer::GetInstance()->GetDevice();
	if ( device )
	{
		LPDIRECT3DTEXTURE9 texture = NULL;
		HRESULT hs = E_FAIL;
		hs = D3DXCreateTexture( device, width, height, level, D3DUSAGE_RENDERTARGET, format, D3DPOOL_DEFAULT, &texture );
		if ( SUCCEEDED( hs ) )
		{
			return_texture = OvNew OvRenderTarget( texture );
		}
	}
	return return_texture;
}
