//#include "OvXmlMeshLoader.h"
//#include "OvRenderer.h"
//#include "OvRenderingCommon.h"
//#include "OvPoint3.h"
//#include "OliveValue.h"
//#include "tinyxml.h"
//
//
//D3DVERTEXELEMENT9 MESH_VERT_ELEMENT[] =
//{
//	{ OvMesh::Low, 0
//	, D3DDECLTYPE_FLOAT3
//	, D3DDECLMETHOD_DEFAULT
//	, D3DDECLUSAGE_POSITION, 0 },
//
//	{ OvMesh::Low, 12
//	, D3DDECLTYPE_FLOAT3
//	, D3DDECLMETHOD_DEFAULT
//	, D3DDECLUSAGE_NORMAL,0},
//
//	{ OvMesh::Medium, 24
//	, D3DDECLTYPE_FLOAT2
//	, D3DDECLMETHOD_DEFAULT
//	, D3DDECLUSAGE_TEXCOORD,0},
//
//	{ OvMesh::Medium, 32
//	, D3DDECLTYPE_FLOAT2
//	, D3DDECLMETHOD_DEFAULT
//	, D3DDECLUSAGE_TEXCOORD,1},
//
//	D3DDECL_END()
//};
//
//typedef struct SStream0Element
//{
//	SStream0Element(const OvPoint3& pos, const OvPoint3& norm)
//		: position( pos )
//		, normal( norm )
//	{
//	};
//	OvPoint3 position;
//	OvPoint3 normal;
//} vertex_geom;
//
//typedef struct SStream1Element
//{
//	SStream1Element(const OvPoint2& difCoord, const OvPoint2& normCoord)
//		: diffuseCoord( difCoord )
//		, normalCoord( normCoord )
//	{
//	};
//	OvPoint2 diffuseCoord;
//	OvPoint2 normalCoord;
//} vertex_texcoord;
//
//typedef std::vector< vertex_geom > geom_buffer;
//typedef std::vector< vertex_texcoord > texcoord_buffer;
//OvResourceSPtr OvXmlMeshLoader::Load( const std::string& fileLocation )
//{
//
//	TiXmlDocument doc;
//	if ( ! doc.LoadFile( fileLocation.c_str() ) )
//	{
//		return false;
//	}
//	TiXmlElement* root = NULL;
//	if ( !( root = doc.RootElement() ) )
//	{
//		return false;
//	}
//
//	geom_buffer geomBuffer;
//	face_buffer		  faceBuffer;
//
//	TiXmlElement* vertexStream = root->FirstChildElement( "VertexStream" );
//	if ( vertexStream )
//	{
//		TiXmlElement* streamLevel = NULL;
//
//		streamLevel = vertexStream->FirstChildElement( "GeomLevel" );
//		for ( TiXmlElement* vert = streamLevel->FirstChildElement("vert")
//			; vert != NULL
//			; vert = vert->NextSiblingElement("vert") )
//		{
//			OliveValue::Point3 pos( vert->Attribute( "pos" ) );
//			OliveValue::Point3 norm( vert->Attribute( "norm" ) );
//			geomBuffer.push_back( vertex_geom( pos.GetPoint3(), norm.GetPoint3() ) );
//		}
//	}
//
//	TiXmlElement* indexStream = root->FirstChildElement( "IndexStream" );
//	if ( indexStream )
//	{
//		for ( TiXmlElement* index = indexStream->FirstChildElement( "index" )
//			; NULL != index 
//			; index  = index ->NextSiblingElement( "index" ))
//		{
//			OliveValue::Point3 faceIndex( index->GetText() );
//			OvPoint3 floatIndex3 = faceIndex.GetPoint3();
//			SFaceIndex shortIndex3( (short)floatIndex3.x, (short)floatIndex3.y, (short)floatIndex3.z );
//			faceBuffer.push_back( shortIndex3 );
//		}
//	}
//
//	OvAutoPtr<SRenderData> renderData = new SRenderData;
//
//	renderData->faceCount = faceBuffer.size();
//	renderData->faceStream = OvRenderer::GetInstance()->CreateIndexStream( &faceBuffer[0], sizeof(face_buffer::value_type), faceBuffer.size());
//	renderData->vertDecl = OvRenderer::GetInstance()->CreateVertexDeclaration( MESH_VERT_ELEMENT );
//	renderData->vertexCount = geomBuffer.size();
//	if ( geomBuffer.size() )
//	{
//		SStreamInfo geomStreamInfo;
//		geomStreamInfo.streamOffset = 0;
//		geomStreamInfo.vertexStream = OvRenderer::GetInstance()->CreateVertexStream( &geomBuffer[0], sizeof(geom_buffer::value_type), geomBuffer.size());;
//		geomStreamInfo.vertexStride = sizeof(geom_buffer::value_type);
//		renderData->vertStreamTable[OvMesh::MeshDetail::Low] = geomStreamInfo;
//	}
//
//	OvMeshSPtr mesh = new OvMesh;
//	SetRenderData( mesh, renderData.Release());
//
//	return mesh;
//
//}