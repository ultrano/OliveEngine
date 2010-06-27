#include "OvMeshBuilder.h"
#include "OvPoint3.h"
#include "OvRenderer.h"
#include "tinyxml.h"
#include "OvMesh.h"



OvMeshBuilder::OvMeshBuilder()
: m_vertexDeclaration( NULL )
, m_faceStreamSource( NULL )
{

};
OvMeshBuilder::~OvMeshBuilder()
{

};
void	OvMeshBuilder::SetGeometryBuffer(const geometry_element_buffer& buffer)
{
	m_geometryBuffer.clear();
	m_geometryBuffer = buffer;
	_push_element_declare
		( 0
		, sizeof( geometry_element_buffer::value_type )
		, D3DDECLTYPE_FLOAT3
		, D3DDECLUSAGE_POSITION
		, m_geometryBuffer.size()
		, (void*)&(m_geometryBuffer[0]) );
}
const geometry_element_buffer&	OvMeshBuilder::GetGeometryBuffer()
{
	return m_geometryBuffer;
}

void	OvMeshBuilder::SetFaceBuffer( const face_element_buffer& buffer )
{
	if ( buffer.empty() == false )
	{
		m_faceBuffer.clear();
		m_faceBuffer = buffer;
	}
}
const face_element_buffer OvMeshBuilder::GetFaceBuffer()
{
	return m_faceBuffer;
}

OvMeshSPtr	OvMeshBuilder::BuildMesh()
{
	LPDIRECT3DDEVICE9 directDevice = (LPDIRECT3DDEVICE9)OvRenderer::GetInstance()->GetDevice();
	if ( directDevice )
	{
		SStreamInfo	streamInfo;
		for each ( SBufferInfo info in m_streamSourceArray )
		{
			LPDIRECT3DVERTEXBUFFER9 vertexStream = NULL;
			vertexStream = _build_vertex_stream( directDevice, info );
			if (vertexStream)
			{
				streamInfo.vertStreamTable[ info.stream ].vertStream = vertexStream;
				streamInfo.vertStreamTable[ info.stream ].vertStride = info.elemSize;
				streamInfo.vertexCount = info.elemCount;
			}
		}
		streamInfo.faceStream = _build_index_stream( directDevice, m_faceBuffer );
		streamInfo.vertDecl = _build_vertex_declare( directDevice );
		streamInfo.faceCount = m_faceBuffer.size();
		return new OvMesh( streamInfo );
	}
	return NULL;
}
LPDIRECT3DVERTEXBUFFER9 OvMeshBuilder::_build_vertex_stream( LPDIRECT3DDEVICE9 directDevice, const SBufferInfo& info )
{
	LPDIRECT3DVERTEXBUFFER9	vertexBuffer = NULL;
	size_t streamSize = info.elemSize * info.elemCount;
	directDevice->CreateVertexBuffer
		( streamSize
		, 0
		, 0
		, D3DPOOL_MANAGED
		, &vertexBuffer
		, NULL);
	if ( vertexBuffer )
	{
		
		void*	copyAddress = NULL;
		if ( SUCCEEDED( vertexBuffer->Lock(0,streamSize,&copyAddress,0) && copyAddress ) )
		{
			memcpy( copyAddress, info.buffer, streamSize);
			vertexBuffer->Unlock();
			return vertexBuffer;
		}
	}
	return NULL;
}
LPDIRECT3DINDEXBUFFER9	OvMeshBuilder::_build_index_stream(  LPDIRECT3DDEVICE9 directDevice, face_element_buffer& faceBuffer )
{
	LPDIRECT3DINDEXBUFFER9 indexStream = NULL;
	if ( directDevice )
	{
		size_t streamSize = sizeof( face_element_buffer::value_type ) * faceBuffer.size();
		directDevice->CreateIndexBuffer
			( streamSize
			, 0
			, D3DFMT_INDEX16
			, D3DPOOL_MANAGED
			, &indexStream
			, NULL
			);
		if ( indexStream )
		{
			void* copyAddress = NULL;
			
			if ( SUCCEEDED( indexStream->Lock( 0, streamSize, &copyAddress,0 ) && copyAddress) )
			{
				memcpy( copyAddress, &(faceBuffer[0]), streamSize );
				indexStream->Unlock();
			}
		}

	}

	return indexStream;
}

void	OvMeshBuilder::_push_element_declare( WORD stream
											 , WORD elemSize
											 , BYTE elemType
											 , BYTE elemUsage
											 , size_t elemCount
											 , void* buffer )
{
	SBufferInfo	vertexDecl;
	vertexDecl.stream = stream;
	vertexDecl.elemSize = elemSize;
	vertexDecl.elemType = elemType;
	vertexDecl.elemUsage = elemUsage;
	vertexDecl.elemCount = elemCount;
	vertexDecl.buffer = buffer;
	m_streamSourceArray.push_back( vertexDecl );
	++m_usageCountTable[elemType];

}
LPDIRECT3DVERTEXDECLARATION9	OvMeshBuilder::_build_vertex_declare( LPDIRECT3DDEVICE9 device )
{
	LPDIRECT3DVERTEXDECLARATION9 vertexDeclaration = NULL;
	if ( device )
	{
		vector<D3DVERTEXELEMENT9> dxVertexDecl;
		SBufferInfo curDecl;
		size_t	lastElemSize = 0;
		for each( curDecl in m_streamSourceArray )
		{
			D3DVERTEXELEMENT9 dxElemDecl;

			dxElemDecl.Stream = curDecl.stream;
			dxElemDecl.Type	  = curDecl.elemType;
			dxElemDecl.Usage  = curDecl.elemUsage;
			dxElemDecl.Method = D3DDECLMETHOD_DEFAULT;
			dxElemDecl.UsageIndex = m_usageCountTable[curDecl.elemType];
			dxElemDecl.Offset = lastElemSize;

			lastElemSize = curDecl.elemSize;

			dxVertexDecl.push_back( dxElemDecl );

		}
		D3DVERTEXELEMENT9 dxEndDecl = D3DDECL_END();
		dxVertexDecl.push_back( dxEndDecl );


		SUCCEEDED(device->CreateVertexDeclaration( &dxVertexDecl[0], &vertexDeclaration ));
	}
	return vertexDeclaration;
}