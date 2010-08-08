#pragma once
#include "OvMemObject.h"
#include "OvRenderingCommon.h"

class OvVertexStream : public OvMemObject
{
public:

	OvVertexStream
		( LPDIRECT3DVERTEXBUFFER9 vertexBuffer
		, WORD streamIndex
		, size_t vertexStride
		, size_t vertexCount
		);

	size_t	GetVertexCount();
	size_t	GetVertexStride();
	size_t	GetStreamSize();
	WORD	GetStreamIndex();

	void	SetCachedStreamOffset(size_t offset);
	size_t	GetCachedStreamOffset();

	LPDIRECT3DVERTEXBUFFER9	GetStreamBuffer();

private:
	
	LPDIRECT3DVERTEXBUFFER9	m_vertexBuffer;

	WORD	m_streamIndex;

	size_t	m_vertexStride;
	size_t	m_vertexCount;

	size_t	m_cachedStreamOffset;

};