#include "OvMesh.h"
#include "OvRenderer.h"
#include "OvRenderingCommon.h"
#include "OvPoint3.h"

OvRTTI_IMPL(OvMesh)


D3DVERTEXELEMENT9 MESH_VERT_ELEMENT[] =
{
	{ OvMesh::Pos_Norm, 0
	, D3DDECLTYPE_FLOAT3
	, D3DDECLMETHOD_DEFAULT
	, D3DDECLUSAGE_POSITION, 0 },

	{ OvMesh::Pos_Norm, 12
	, D3DDECLTYPE_FLOAT3
	, D3DDECLMETHOD_DEFAULT
	, D3DDECLUSAGE_NORMAL,0},

	D3DDECL_END()
};

typedef struct SStream0Element
{
	SStream0Element(const OvPoint3& pos, const OvPoint3& norm)
		: position( pos )
		, normal( norm )
	{
	};
	OvPoint3 position;
	OvPoint3 normal;
} stream_0_element;

typedef std::vector< stream_0_element > stream_0_buffer;

OvMesh::OvMesh()
{

}

OvMesh::~OvMesh()
{

}
bool OvMesh::Load( const std::string& fileLocation )
{
	OvAutoPtr<SRenderData> renderData = new SRenderData;
	stream_0_buffer vertBuffer;
	vertBuffer.push_back( stream_0_element( OvPoint3( 0, 0, 0 ), OvPoint3() ) );
	vertBuffer.push_back( stream_0_element( OvPoint3( 0, 1, 0 ), OvPoint3() ) );
	vertBuffer.push_back( stream_0_element( OvPoint3( 1, 0, 0 ), OvPoint3() ) );
	vertBuffer.push_back( stream_0_element( OvPoint3( 1, 1, 0 ), OvPoint3() ) );


	index_buffer	indexBuffer;
	indexBuffer.push_back( index_element( 0, 1, 2 ) );
	indexBuffer.push_back( index_element( 3, 1, 2 ) );

	size_t vertCount = vertBuffer.size();
	SVertexStreamInfo vertStreamInfo;
	
	vertStreamInfo.vertexStride = sizeof( stream_0_element );
	vertStreamInfo.vertexStream = OvRenderer::GetInstance()->CreateVertexStream( &vertBuffer[0], vertStreamInfo.vertexStride, vertCount );

	renderData->vertStreamTable[ RenderLevel::Pos_Norm ] = vertStreamInfo;
	renderData->vertexCount = vertCount;

	renderData->faceStream = OvRenderer::GetInstance()->CreateIndexStream( &indexBuffer[0], sizeof( index_buffer ), indexBuffer.size() );
	renderData->faceCount = indexBuffer.size();

	renderData->vertDecl = OvRenderer::GetInstance()->CreateVertexDeclaration( MESH_VERT_ELEMENT );

	m_renderData = renderData.Release();

	return false;
}
void	OvMesh::Rendering()
{
	for each( vertex_stream_table::value_type tableElem in m_renderData->vertStreamTable )
	{
		OvRenderer::GetInstance()->SetVertexStream( tableElem.first, &tableElem.second );
	}

	OvRenderer::GetInstance()->SetIndexStream( m_renderData->faceStream );

	OvRenderer::GetInstance()->SetVertexDeclaration( m_renderData->vertDecl );

	bool result = OvRenderer::GetInstance()->DrawIndexedPrimitive( D3DPRIMITIVETYPE::D3DPT_TRIANGLELIST, m_renderData->vertexCount, m_renderData->faceCount );

	if ( result )
	{
		OutputDebugStr("success\n");
	}
	else
	{
		OutputDebugStr("failed\n");
	}
}
