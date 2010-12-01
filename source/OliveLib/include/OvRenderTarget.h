//#pragma once
//#include "OvTexture.h"
//
//OvREF_POINTER( OvRenderTarget );
//class OvMatrix;
//class OvPoint3;
//
//// 음... 굳이 이런 클레스가 필요 없을거 같다라는 느낌이 온다...
//// OvRenderer의 ChangeRenderTarget, ChangeDepthStencil 메소드로 충분한 해결이 가능할것 같은데...?
//// 음.. 좀더 사용빈도를 지켜보고 유지할지의 여부를 정해야 겠다
//class OvRenderTarget : public OvMemObject
//{
//public:
//
//	OvRenderTarget();
//	~OvRenderTarget();
//
//	bool	LockRenderTarget( unsigned render_target_index, LPDIRECT3DSURFACE9 renderTarget );
//	bool	UnlockRenderTarget();
//
//	bool	LockDepthStencil( LPDIRECT3DSURFACE9 depthStencil );
//	bool	UnlockDepthStencil();
//
//	// test method
//	void	CubeFaceMatrix( D3DCUBEMAP_FACES face_index, const OvPoint3& cube_pos, OvMatrix& outMat );
//
//private:
//	OvInt m_reservedRenderTargetIndex;
//	LPDIRECT3DSURFACE9 m_oldRenderTarget;
//	LPDIRECT3DSURFACE9 m_oldDepthStencil;
//
//};