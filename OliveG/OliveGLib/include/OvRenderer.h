#pragma once
#include "OvUtility.h"
#include "OvMemObject.h"
#include "OvAutoPtr.h"
#include "OvRefBase.h"
#include "OvSingleton.h"
#include "OvRenderingCommon.h"


class OvRenderer : public OvSingletonBase< OvRenderer >
{
	OvRTTI_DECL_ROOT(OvRenderer);
public:

	OvRenderer();
	~OvRenderer();

	bool			GenerateRenderer(HWND _hTargetWindowHangle);

	bool			ClearTarget();
	bool			BeginTarget();
	bool			EndTarget();
	bool			PresentTarget();

	void			SetVertexStream( WORD streamIndex, SVertexStreamInfo* streamInfo );
	void			SetIndexStream( LPDIRECT3DINDEXBUFFER9 streamBuffer );
	void			SetVertexDeclaration( LPDIRECT3DVERTEXDECLARATION9 decl );
	bool			DrawIndexedPrimitive( D3DPRIMITIVETYPE primitiveType, size_t vertCount, size_t faceCount );

//////////////////////////////////////////////////////////////////////////

	LPDIRECT3DVERTEXBUFFER9 CreateVertexStream( void* buffer, size_t stride, size_t count );
	LPDIRECT3DINDEXBUFFER9	CreateIndexStream( void* buffer, size_t stride, size_t count);
	LPDIRECT3DVERTEXDECLARATION9 CreateVertexDeclaration( D3DVERTEXELEMENT9* vertElement );
	LPDIRECT3DDEVICE9	GetDevice();

private:

	LPDIRECT3DDEVICE9			m_device;

};


