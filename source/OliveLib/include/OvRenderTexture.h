#pragma once
#include "OvTexture.h"

OvREF_POINTER( OvRenderTarget );

// ��... ���� �̷� Ŭ������ �ʿ� ������ ���ٶ�� ������ �´�...
// OvRenderer�� ChangeRenderTarget, ChangeDepthStencil �޼ҵ�� ����� �ذ��� �����Ұ� ������...?
// ��.. ���� ���󵵸� ���Ѻ��� ���������� ���θ� ���ؾ� �ڴ�
class OvRenderTarget : public OvMemObject
{
public:

	OvRenderTarget();
	~OvRenderTarget();

	bool	LockRenderTarget( unsigned render_target_index, LPDIRECT3DSURFACE9 renderTarget );
	bool	UnlockRenderTarget();

	bool	LockDepthStencil( LPDIRECT3DSURFACE9 depthStencil );
	bool	UnlockDepthStencil();

private:
	int m_reservedRenderTargetIndex;
	LPDIRECT3DSURFACE9 m_oldRenderTarget;
	LPDIRECT3DSURFACE9 m_oldDepthStencil;

};
OvTextureSPtr CreateRenderTexture( unsigned width, unsigned height, unsigned level, D3DFORMAT format );
OvTextureSPtr CreateDepthStencilTexture( unsigned width, unsigned height, unsigned level, D3DFORMAT format );