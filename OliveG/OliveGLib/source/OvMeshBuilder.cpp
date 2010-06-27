#include "OvMeshBuilder.h"
#include "OvPoint3.h"
#include "OvRenderer.h"
#include "tinyxml.h"
#include "OvMesh.h"



bool OvMeshBuilder::LoadMesh(/*블라 블라*/)
{
	SRenderData	renderData;
	renderData.vertexCount	= 4;
	renderData.faceCount	= 6;
	renderData.vertStreamTable = m_vertexStreamTable;
	//renderData.faceStream	= CreateIndexStream();
	m_device->CreateVertexDeclaration(MESH_VERT_ELEMENT,&renderData.vertDecl);
	return true;
}
bool OvMeshBuilder::BuildVertexStream0(explicit stream_0_element_buffer& buffer)
{
	if ( m_device )
	{
		size_t elemSize = sizeof( stream_0_element_buffer::value_type );
		size_t streamSize = buffer.size() * elemSize;
		SVertexStreamInfo	streamInfo;
		HRESULT hr = m_device->CreateVertexBuffer
			( streamSize
			, 0
			, 0
			, D3DPOOL_MANAGED
			, &streamInfo.vertexStream
			, NULL
			);
		if ( SUCCEEDED(hr) && streamInfo.vertexStream )
		{
			void* copyDest = NULL;
			if ( SUCCEEDED(streamInfo.vertexStream->Lock( 0, streamSize, &copyDest, 0)) && copyDest)
			{
				memcpy( copyDest, &buffer[0], streamSize );
				streamInfo.vertexStream->Unlock();
				streamInfo.vertexStride = elemSize;
				m_vertexStreamTable[Pos_Norm] = streamInfo;
				return true;
			}
		}
	}
	return false;
}
LPDIRECT3DINDEXBUFFER9	OvMeshBuilder::CreateIndexStream(explicit face_element_buffer& buffer)
{
	if ( m_device )
	{
		LPDIRECT3DINDEXBUFFER9	streamBuffer = NULL;
		size_t elemSize = sizeof( face_element_buffer::value_type );
		size_t streamSize = buffer.size() * elemSize;
		HRESULT hr = m_device->CreateIndexBuffer
			( streamSize
			, 0
			, D3DFMT_INDEX16
			, D3DPOOL_MANAGED
			, &streamBuffer
			, NULL
			);

		if ( SUCCEEDED(hr) && streamBuffer )
		{
			void* copyDest = NULL;
			if ( SUCCEEDED(streamBuffer->Lock( 0, streamSize, &copyDest, 0)) && copyDest)
			{
				memcpy( copyDest, &buffer[0], streamSize );
				streamBuffer->Unlock();
				return streamBuffer;
			}
		}
	}
	return NULL;
}