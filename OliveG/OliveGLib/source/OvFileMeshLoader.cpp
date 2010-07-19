#include "OvFileMeshLoader.h"
#include "OvRenderer.h"
#include "OliveValue.h"
#include "OvPoint2.h"
#include "OvPoint3.h"

OvRTTI_IMPL(OvFileMeshLoader);
//////////////////////////////////////////////////////////////////////////
//////////////////////////////////////////////////////////////////////////
//////////////////////////////////////////////////////////////////////////
//////////////////////////////////////////////////////////////////////////
//////////////////////////////////////////////////////////////////////////
//////////////////////////////////////////////////////////////////////////
D3DVERTEXELEMENT9 MESH_ELEMENT[] =
{
	{ OvMesh::Geometry, 0
	, D3DDECLTYPE_FLOAT3
	, D3DDECLMETHOD_DEFAULT
	, D3DDECLUSAGE_POSITION, 0 },

	{ OvMesh::Geometry, 12
	, D3DDECLTYPE_FLOAT3
	, D3DDECLMETHOD_DEFAULT
	, D3DDECLUSAGE_NORMAL, 0 },

	{ OvMesh::Geometry, 24
	, D3DDECLTYPE_FLOAT3
	, D3DDECLMETHOD_DEFAULT
	, D3DDECLUSAGE_TANGENT, 0 },


	{ OvMesh::TextureCoord, 0
	, D3DDECLTYPE_FLOAT2
	, D3DDECLMETHOD_DEFAULT
	, D3DDECLUSAGE_TEXCOORD, 0 },


	D3DDECL_END()
};

struct SVertex_Low
{
	SVertex_Low(){};
	SVertex_Low
		( const OvPoint3& in_pos
		, const OvPoint3& in_norm
		, const OvPoint3& in_tan)
		: pos( in_pos )
		, norm( in_norm )
		, tan( in_tan )
	{
	};
	OvPoint3 pos;
	OvPoint3 norm;
	OvPoint3 tan;
};
typedef vector<SVertex_Low> low_stream_buffer;

struct SVertex_Medium
{
	SVertex_Medium(){};
	SVertex_Medium(const OvPoint2& in_tex0)
		: tex0( in_tex0 )
	{
	};
	OvPoint2 tex0;
};
typedef vector<SVertex_Medium> medium_stream_buffer;

//////////////////////////////////////////////////////////////////////////
//////////////////////////////////////////////////////////////////////////
//////////////////////////////////////////////////////////////////////////
//////////////////////////////////////////////////////////////////////////
//////////////////////////////////////////////////////////////////////////
//////////////////////////////////////////////////////////////////////////
OvResourceSPtr OvFileMeshLoader::Load( const std::string& fileLocation )
{
	FILE* meshFile = m_file = fopen( fileLocation.c_str(), "r" );
	if ( NULL == meshFile )
	{
		return NULL;
	}

	SVertexStreamInfo streamInfoLow;
	SVertexStreamInfo streamInfoMedium;
	SVertexStreamInfo streamInfoHigh;
	LPDIRECT3DINDEXBUFFER9	  streamFace = NULL;

	

	OliveValue::Integer vertexCount( _readLine() );
	OliveValue::Integer faceCount( _readLine() );
	streamInfoLow = _parseStreamLow();
	streamInfoMedium = _parseStreamMedium();
	streamFace = _parseIndexStream();

	fclose( meshFile );
	return _buildMesh
		( streamInfoLow
		, streamInfoMedium
		, streamInfoHigh
		, OvRenderer::GetInstance()->CreateVertexDeclaration( MESH_ELEMENT )
		, vertexCount.GetInteger()
		, streamFace
		, faceCount.GetInteger() );

}


const char* OvFileMeshLoader::_readLine()
{
	fscanf( m_file, "%s", &m_readBuffer );
	return m_readBuffer;
}

SVertexStreamInfo OvFileMeshLoader::_parseStreamLow()
{
	OliveValue::Integer vertNum;
	
	low_stream_buffer bufferLow;

	vector< OvPoint3 > posBuffer;
	vector< OvPoint3 > normBuffer;
	vector< OvPoint3 > tanBuffer;

	vertNum.SetValue( _readLine() );
	for ( unsigned i = 0 ; i < vertNum.GetInteger() ; ++i )
	{
		OliveValue::Point3 pos( _readLine() );
		posBuffer.push_back( pos.GetPoint3() );
	}
	for ( unsigned i = 0 ; i < vertNum.GetInteger() ; ++i )
	{
		OliveValue::Point3 norm( _readLine() );
		normBuffer.push_back( norm.GetPoint3() );
	}
	for ( unsigned i = 0 ; i < vertNum.GetInteger() ; ++i )
	{
		OliveValue::Point3 tan( _readLine() );
		tanBuffer.push_back( tan.GetPoint3() );
	}
	for ( unsigned i = 0 ; i < vertNum.GetInteger() ; ++i )
	{
		SVertex_Low vertexLow
			( posBuffer.at( i )
			, normBuffer.at( i )
			, tanBuffer.at( i ));
		bufferLow.push_back( vertexLow );
	}


	SVertexStreamInfo streamInfo;
	if ( bufferLow.size() )
	{
		streamInfo.streamOffset = 0;
		streamInfo.vertexStride = sizeof(SVertex_Low);
		streamInfo.vertexStream = OvRenderer::GetInstance()->CreateVertexStream
			( &(bufferLow[0])
			, streamInfo.vertexStride
			, bufferLow.size() );
	}

	return streamInfo;
}

SVertexStreamInfo OvFileMeshLoader::_parseStreamMedium()
{
	SVertexStreamInfo streamInfo;
	medium_stream_buffer buffer;

	OliveValue::Integer vertCount( _readLine() );
	for ( unsigned i = 0 ; i < vertCount.GetInteger() ; ++i )
	{
		OliveValue::Point2 tvert( _readLine() );
		SVertex_Medium vertex;
		vertex.tex0 = tvert.GetPoint2();
		buffer.push_back( vertex );
	}
	if ( buffer.size() )
	{
		streamInfo.streamOffset = 0;
		streamInfo.vertexStride = sizeof(SVertex_Medium);
		streamInfo.vertexStream = OvRenderer::GetInstance()->CreateVertexStream
			( &(buffer[0])
			, streamInfo.vertexStride
			, buffer.size() );
	}

	return streamInfo;
}

LPDIRECT3DINDEXBUFFER9 OvFileMeshLoader::_parseIndexStream()
{
	LPDIRECT3DINDEXBUFFER9	indexStream = NULL;
	OliveValue::Integer faceCount( _readLine() );
	face_buffer faceBuffer;

	for ( size_t i = 0 ; i < faceCount.GetInteger() ; ++i)
	{
		OliveValue::Point3 readIndex( _readLine() );
		OvPoint3 findex3 = readIndex.GetPoint3();
		faceBuffer.push_back( SFaceIndex( (short)findex3.x, (short)findex3.y, (short)findex3.z ) );
	}
	if ( faceBuffer.size() )
	{
		indexStream = OvRenderer::GetInstance()->CreateIndexStream
			( &faceBuffer[0]
			, sizeof(SFaceIndex)
			, faceBuffer.size() );
	}
	return indexStream;
}
