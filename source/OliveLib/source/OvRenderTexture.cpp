#include "OvRenderTexture.h"
#include "OvRenderer.h"
#include "OvMatrix.h"
 
OvRenderTarget::OvRenderTarget()
: m_reservedRenderTargetIndex( -1 )
, m_oldRenderTarget( NULL )
, m_oldDepthStencil( NULL )
{

}

OvRenderTarget::~OvRenderTarget()
{
	if ( m_oldRenderTarget )
	{
		m_oldRenderTarget->Release();
		m_oldRenderTarget = NULL;
	}
	if ( m_oldDepthStencil )
	{
		m_oldDepthStencil->Release();
		m_oldDepthStencil = NULL;
	}
}
bool OvRenderTarget::LockRenderTarget( unsigned render_target_index, LPDIRECT3DSURFACE9 renderTarget )
{
	if ( -1 == m_reservedRenderTargetIndex )
	{
		m_oldRenderTarget = OvRenderer::GetInstance()->ChangeRenderTarget( render_target_index, renderTarget );
		if ( m_oldRenderTarget )
		{
			m_reservedRenderTargetIndex = render_target_index;
			return m_oldRenderTarget;
		}
	}
	return false;
}

bool OvRenderTarget::UnlockRenderTarget()
{
	if ( m_oldRenderTarget && -1 != m_reservedRenderTargetIndex )
	{
		OvRenderer::GetInstance()->ChangeRenderTarget( m_reservedRenderTargetIndex, m_oldRenderTarget );
		m_oldRenderTarget->Release();
		m_oldRenderTarget = NULL;
		m_reservedRenderTargetIndex = -1;
		return true;
	}
	return false;
}

bool OvRenderTarget::LockDepthStencil( LPDIRECT3DSURFACE9 depthStencil )
{
	m_oldDepthStencil = OvRenderer::GetInstance()->ChangeDepthStencil( depthStencil );
	return m_oldDepthStencil;
}

bool OvRenderTarget::UnlockDepthStencil()
{
	if ( m_oldDepthStencil )
	{
		OvRenderer::GetInstance()->ChangeDepthStencil( m_oldDepthStencil );
		m_oldDepthStencil->Release();
		m_oldDepthStencil = NULL;
		return true;
	}
	return false;
}

const OvMatrix& OvRenderTarget::CubeFaceMatrix( D3DCUBEMAP_FACES face_index, const OvPoint3& pt )
{
	OvPoint3 krWorldPoint(pt);
	OvPoint3 krLookDir;
	OvPoint3 krUpDir;

	switch( face_index )
	{
	case D3DCUBEMAP_FACE_POSITIVE_X:
		krLookDir = OvPoint3( 1.0f, 0.0f, 0.0f );
		krUpDir   = OvPoint3( 0.0f, 1.0f, 0.0f );
		break;
	case D3DCUBEMAP_FACE_NEGATIVE_X:
		krLookDir = OvPoint3(-1.0f, 0.0f, 0.0f );
		krUpDir   = OvPoint3( 0.0f, 1.0f, 0.0f );
		break;
	case D3DCUBEMAP_FACE_POSITIVE_Y:
		krLookDir = OvPoint3( 0.0f, 1.0f, 0.0f );
		krUpDir   = OvPoint3( 0.0f, 0.0f,-1.0f );
		break;
	case D3DCUBEMAP_FACE_NEGATIVE_Y:
		krLookDir = OvPoint3( 0.0f,-1.0f, 0.0f );
		krUpDir   = OvPoint3( 0.0f, 0.0f, 1.0f );
		break;
	case D3DCUBEMAP_FACE_POSITIVE_Z:
		krLookDir = OvPoint3( 0.0f, 0.0f, 1.0f );
		krUpDir   = OvPoint3( 0.0f, 1.0f, 0.0f );
		break;
	case D3DCUBEMAP_FACE_NEGATIVE_Z:
		krLookDir = OvPoint3( 0.0f, 0.0f,-1.0f );
		krUpDir   = OvPoint3( 0.0f, 1.0f, 0.0f );
		break;
	}

	OvPoint3 krRightDir	= OvPoint3CrossProduct( krUpDir, krLookDir );

	static OvMatrix test;
	test = OvMatrix
		(krRightDir.x,krUpDir.x,krLookDir.x,0
		,krRightDir.y,krUpDir.y,krLookDir.y,0
		,krRightDir.z,krUpDir.z,krLookDir.z,0
		,-krRightDir.DotProduct(krWorldPoint),-krUpDir.DotProduct(krWorldPoint),-krLookDir.DotProduct(krWorldPoint),1);

	return test;

}
// 
// bool OvRenderTexture::Unlock()
// {
// 	if ( m_reservedTargetIndex != -1 )
// 	{
// 		LPDIRECT3DDEVICE9 device = OvRenderer::GetInstance()->GetDevice();
// 		if ( device && m_oldTargetSurface )
// 		{
// 
// 			//////////  testing  ///////////////////////////////////////////////
// 			if ( SUCCEEDED( device->SetDepthStencilSurface( m_oldDepthSurface ) ) )
// 			{
// 				m_oldDepthSurface->Release();
// 				m_oldDepthSurface = NULL;
// 			}
// 			//////////////////////////////////////////////////////////////////////////
// 
// 			if ( SUCCEEDED( device->SetRenderTarget( m_reservedTargetIndex, m_oldTargetSurface ) ) )
// 			{
// 				m_oldTargetSurface->Release();
// 				m_oldTargetSurface = NULL;
// 				m_reservedTargetIndex = -1;
// 				return true;
// 			}
// 		}
// 	}
// 	return false;
// }

//////////////////////////////////////////////////////////////////////////
//////////////////////////////////////////////////////////////////////////
//////////////////////////////////////////////////////////////////////////


OvTextureSPtr CreateRenderTexture( unsigned width, unsigned height, unsigned level, D3DFORMAT format )
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
			return_texture = OvNew OvTexture( texture );
		}
	}
	return return_texture;
}

OvTextureSPtr CreateDepthStencilTexture( unsigned width, unsigned height, unsigned level, D3DFORMAT format )
{
	OvTextureSPtr return_texture = NULL;
	LPDIRECT3DDEVICE9 device = OvRenderer::GetInstance()->GetDevice();
	if ( device )
	{
		LPDIRECT3DTEXTURE9 texture = NULL;
		HRESULT hs = E_FAIL;
		hs = D3DXCreateTexture( device, width, height, level, D3DUSAGE_DEPTHSTENCIL, format, D3DPOOL_DEFAULT, &texture );
		if ( SUCCEEDED( hs ) )
		{
			return_texture = OvNew OvTexture( texture );
		}
	}
	return return_texture;
}

OvCubeTextureSPtr CreateRenderCubeTexture( unsigned size, unsigned level, D3DFORMAT format )
{
	OvCubeTextureSPtr return_texture = NULL;
	LPDIRECT3DDEVICE9 device = OvRenderer::GetInstance()->GetDevice();
	if ( device )
	{
		LPDIRECT3DCUBETEXTURE9 cube_texture = NULL;
		HRESULT hs = E_FAIL;
		hs = D3DXCreateCubeTexture( device, size,level, D3DUSAGE_RENDERTARGET, format, D3DPOOL_DEFAULT, &cube_texture );
		if ( SUCCEEDED( hs ) )
		{
			return_texture = OvNew OvCubeTexture( cube_texture );
		}
	}
	return return_texture;
}