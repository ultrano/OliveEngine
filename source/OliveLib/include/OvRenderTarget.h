//#pragma once
//#include "OvTexture.h"
//
//OvREF_POINTER( OvRenderTarget );
//class OvMatrix;
//class OvPoint3;
//
//// ��... ���� �̷� Ŭ������ �ʿ� ������ ���ٶ�� ������ �´�...
//// OvRenderer�� ChangeRenderTarget, ChangeDepthStencil �޼ҵ�� ����� �ذ��� �����Ұ� ������...?
//// ��.. ���� ���󵵸� ���Ѻ��� ���������� ���θ� ���ؾ� �ڴ�
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