#include "OvVertexStream.h"


OvVertexStream::OvVertexStream( LPDIRECT3DVERTEXBUFFER9 vertexBuffer , WORD streamIndex , size_t vertexStride , size_t vertexCount ) : m_vertexBuffer( vertexBuffer )
, m_streamIndex( streamIndex )
, m_vertexStride( vertexStride )
, m_vertexCount( vertexCount )
{

}

LPDIRECT3DVERTEXBUFFER9 OvVertexStream::GetStreamBuffer()
{
	return m_vertexBuffer;
}

size_t OvVertexStream::GetCachedStreamOffset()
{
	return m_cachedStreamOffset;
}

void OvVertexStream::SetCachedStreamOffset( size_t offset )
{
	m_cachedStreamOffset = offset;
}

size_t OvVertexStream::GetStreamSize()
{
	return m_vertexCount*m_vertexStride;
}

size_t OvVertexStream::GetVertexStride()
{
	return m_vertexStride;
}

size_t OvVertexStream::GetVertexCount()
{
	return m_vertexCount;
}

WORD OvVertexStream::GetStreamIndex()
{
	return m_streamIndex;
}