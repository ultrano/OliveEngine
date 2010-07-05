#include "OvMesh.h"
#include "OvRenderer.h"
#include "OvRenderingCommon.h"
#include "OvPoint3.h"
#include "OliveValue.h"
#include "tinyxml.h"

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

	{ OvMesh::Diff_Norm_TexCoord, 24
	, D3DDECLTYPE_FLOAT2
	, D3DDECLMETHOD_DEFAULT
	, D3DDECLUSAGE_TEXCOORD,0},

	{ OvMesh::Diff_Norm_TexCoord, 32
	, D3DDECLTYPE_FLOAT2
	, D3DDECLMETHOD_DEFAULT
	, D3DDECLUSAGE_TEXCOORD,1},

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

typedef struct SStream1Element
{
	SStream1Element(const OvPoint2& difCoord, const OvPoint2& normCoord)
		: diffuseCoord( difCoord )
		, normalCoord( normCoord )
	{
	};
	OvPoint2 diffuseCoord;
	OvPoint2 normalCoord;
} stream_1_element;

typedef std::vector< stream_0_element > stream_0_buffer;
typedef std::vector< stream_1_element > stream_1_buffer;

OvMesh::OvMesh()
{

}

OvMesh::~OvMesh()
{

}
bool OvMesh::Load( const std::string& fileLocation )
{
	TiXmlDocument doc;
	doc.LoadFile( fileLocation.c_str() );
	TiXmlElement* elem = doc.RootElement();
	TiXmlElement* vertStream = elem->FirstChildElement("VertexStream");

	OvAutoPtr<SRenderData> renderData = new SRenderData;

	TiXmlElement* stream = vertStream->FirstChildElement("Stream");
	if ( NULL != stream)
	{
		stream_0_buffer vertBuffer;

		for ( TiXmlElement* vert = stream->FirstChildElement()
			; NULL != vert
			; vert = vert->NextSiblingElement())
		{
			OliveValue::Point3 pos( vert->Attribute( "pos" ) );
			OliveValue::Point3 norm( vert->Attribute( "norm" ) );

			vertBuffer.push_back( stream_0_element( pos.GetPoint3(), norm.GetPoint3() ) );
		}

		size_t vertCount = vertBuffer.size();
		SVertexStreamInfo vertStreamInfo;
		vertStreamInfo.vertexStride = sizeof( stream_0_element );
		vertStreamInfo.vertexStream = OvRenderer::GetInstance()->CreateVertexStream( &vertBuffer[0], vertStreamInfo.vertexStride, vertCount );

		renderData->vertStreamTable[ RenderLevel::Pos_Norm ] = vertStreamInfo;
		renderData->vertexCount = vertCount;
	}

	TiXmlElement* indexStream = elem->FirstChildElement("IndexStream");

	if ( NULL != indexStream )
	{
		index_buffer	indexBuffer;

		for ( TiXmlElement* index = indexStream->FirstChildElement()
			; NULL != index
			; index = index->NextSiblingElement())
		{
			OliveValue::Point3 face( index->GetText() );
			indexBuffer.push_back( index_element( face.GetPoint3().x, face.GetPoint3().y, face.GetPoint3().z ) );
		}

		size_t faceCount = indexBuffer.size();
		renderData->faceStream = OvRenderer::GetInstance()->CreateIndexStream( &indexBuffer[0], sizeof( index_buffer ), faceCount );
		renderData->faceCount = faceCount;
	}

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

}
