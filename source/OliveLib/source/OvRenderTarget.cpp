//#include "OvRenderTarget.h"
//#include "OvRenderer.h"
//#include "OvMatrix.h"
//#include "OvTransform.h"
// 
//OvRenderTarget::OvRenderTarget()
//: m_reservedRenderTargetIndex( -1 )
//, m_oldRenderTarget( NULL )
//, m_oldDepthStencil( NULL )
//{
//
//}
//
//OvRenderTarget::~OvRenderTarget()
//{
//	if ( m_oldRenderTarget )
//	{
//		m_oldRenderTarget->Release();
//		m_oldRenderTarget = NULL;
//	}
//	if ( m_oldDepthStencil )
//	{
//		m_oldDepthStencil->Release();
//		m_oldDepthStencil = NULL;
//	}
//}
//OvBool OvRenderTarget::LockRenderTarget( unsigned render_target_index, LPDIRECT3DSURFACE9 renderTarget )
//{
//	if ( -1 == m_reservedRenderTargetIndex )
//	{
//		m_oldRenderTarget = OvRenderer::GetInstance()->SetRenderTarget( render_target_index, renderTarget );
//		if ( m_oldRenderTarget )
//		{
//			m_reservedRenderTargetIndex = render_target_index;
//			return ( m_oldRenderTarget != NULL );
//		}
//	}
//	return false;
//}
//
//OvBool OvRenderTarget::UnlockRenderTarget()
//{
//	if ( m_oldRenderTarget && -1 != m_reservedRenderTargetIndex )
//	{
//		OvRenderer::GetInstance()->SetRenderTarget( m_reservedRenderTargetIndex, m_oldRenderTarget );
//		m_oldRenderTarget->Release();
//		m_oldRenderTarget = NULL;
//		m_reservedRenderTargetIndex = -1;
//		return true;
//	}
//	return false;
//}
//
//OvBool OvRenderTarget::LockDepthStencil( LPDIRECT3DSURFACE9 depthStencil )
//{
//	m_oldDepthStencil = OvRenderer::GetInstance()->SetDepthStencil( depthStencil );
//	return ( m_oldDepthStencil != NULL );
//}
//
//OvBool OvRenderTarget::UnlockDepthStencil()
//{
//	if ( m_oldDepthStencil )
//	{
//		OvRenderer::GetInstance()->SetDepthStencil( m_oldDepthStencil );
//		m_oldDepthStencil->Release();
//		m_oldDepthStencil = NULL;
//		return true;
//	}
//	return false;
//}
//
//void OvRenderTarget::CubeFaceMatrix( D3DCUBEMAP_FACES face_index, const OvPoint3& cube_pos, OvMatrix& outMat )
//{
//	OvPoint3 lookDir;
//	OvPoint3 upDir;
//
//	switch( face_index )
//	{
//	case D3DCUBEMAP_FACE_POSITIVE_X:
//		lookDir = OvPoint3( 1.0f, 0.0f, 0.0f );
//		upDir   = OvPoint3( 0.0f, 1.0f, 0.0f );
//		break;
//	case D3DCUBEMAP_FACE_NEGATIVE_X:
//		lookDir = OvPoint3(-1.0f, 0.0f, 0.0f );
//		upDir   = OvPoint3( 0.0f, 1.0f, 0.0f );
//		break;
//	case D3DCUBEMAP_FACE_POSITIVE_Y:
//		lookDir = OvPoint3( 0.0f, 1.0f, 0.0f );
//		upDir   = OvPoint3( 0.0f, 0.0f,-1.0f );
//		break;
//	case D3DCUBEMAP_FACE_NEGATIVE_Y:
//		lookDir = OvPoint3( 0.0f,-1.0f, 0.0f );
//		upDir   = OvPoint3( 0.0f, 0.0f, 1.0f );
//		break;
//	case D3DCUBEMAP_FACE_POSITIVE_Z:
//		lookDir = OvPoint3( 0.0f, 0.0f, 1.0f );
//		upDir   = OvPoint3( 0.0f, 1.0f, 0.0f );
//		break;
//	case D3DCUBEMAP_FACE_NEGATIVE_Z:
//		lookDir = OvPoint3( 0.0f, 0.0f,-1.0f );
//		upDir   = OvPoint3( 0.0f, 1.0f, 0.0f );
//		break;
//	}
//
//	MakeViewMatrix( lookDir, upDir, cube_pos, outMat );
//
//}
//// 
//// OvBool OvRenderTexture::Unlock()
//// {
//// 	if ( m_reservedTargetIndex != -1 )
//// 	{
//// 		LPDIRECT3DDEVICE9 device = OvRenderer::GetInstance()->GetDevice();
//// 		if ( device && m_oldTargetSurface )
//// 		{
//// 
//// 			//////////  testing  ///////////////////////////////////////////////
//// 			if ( SUCCEEDED( device->SetDepthStencilSurface( m_oldDepthSurface ) ) )
//// 			{
//// 				m_oldDepthSurface->Release();
//// 				m_oldDepthSurface = NULL;
//// 			}
//// 			//////////////////////////////////////////////////////////////////////////
//// 
//// 			if ( SUCCEEDED( device->SetRenderTarget( m_reservedTargetIndex, m_oldTargetSurface ) ) )
//// 			{
//// 				m_oldTargetSurface->Release();
//// 				m_oldTargetSurface = NULL;
//// 				m_reservedTargetIndex = -1;
//// 				return true;
//// 			}
//// 		}
//// 	}
//// 	return false;
//// }
//
////////////////////////////////////////////////////////////////////////////
////////////////////////////////////////////////////////////////////////////
////////////////////////////////////////////////////////////////////////////
//
