#include "OvFileMeshLoader.h"
#include "OvRenderer.h"
#include "OliveValue.h"
#include "OvPoint2.h"
#include "OvPoint3.h"
#include "OvDataStream.h"

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


OvFileMeshLoader::OvFileMeshLoader()
{
	m_readBuffer.resize( MAX_READ_BUFFER_SIZE );
}

OvFileMeshLoader::~OvFileMeshLoader()
{
	m_readBuffer.clear();
}

OvResourceSPtr OvFileMeshLoader::Load( OvDataStream& stream )
{
	m_data = &stream;

	SVertexStreamInfo streamInfoLow;
	SVertexStreamInfo streamInfoMedium;
	SVertexStreamInfo streamInfoHigh;
	LPDIRECT3DINDEXBUFFER9	  streamFace = NULL;

	OliveValue::Integer vertexCount( _readLine() );
	OliveValue::Integer faceCount( _readLine() );
	streamInfoLow = _parseStreamLow();
	streamInfoMedium = _parseStreamMedium();
	streamFace = _parseIndexStream();

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
	// fgets() 의 특성상 '\n' 개행 문자가 끌려 온다.
	// 개행 문자가 있으면 문자를 다른 데이터타입으로 변환시 
	// 문제가 발생할수 있으므로 '\0'터미널 문자로 바꿔준다.
	m_data->ReadLine( m_readBuffer );
	return m_readBuffer.c_str();
}

SVertexStreamInfo OvFileMeshLoader::_parseStreamLow()
{
	OliveValue::Integer vertNum;
	
	low_stream_buffer bufferLow;

	vector< OvPoint3 > posBuffer;
	vector< OvPoint3 > normBuffer;
	vector< OvPoint3 > tanBuffer;

	vertNum.SetValue( _readLine() );
	posBuffer.reserve( vertNum.GetInteger() );
	for ( unsigned i = 0 ; i < (unsigned)vertNum.GetInteger() ; ++i )
	{
		OliveValue::Point3 pos( _readLine() );
		posBuffer.push_back( pos.GetPoint3() );
	}

	normBuffer.reserve( vertNum.GetInteger() );
	for ( unsigned i = 0 ; i < (unsigned)vertNum.GetInteger() ; ++i )
	{
		OliveValue::Point3 norm( _readLine() );
		normBuffer.push_back( norm.GetPoint3() );
	}

	tanBuffer.reserve( vertNum.GetInteger() );
	for ( unsigned i = 0 ; i < (unsigned)vertNum.GetInteger() ; ++i )
	{
		OliveValue::Point3 tan( _readLine() );
		tanBuffer.push_back( tan.GetPoint3() );
	}

	bufferLow.reserve( vertNum.GetInteger() );
	for ( unsigned i = 0 ; i < (unsigned)vertNum.GetInteger() ; ++i )
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
			, (UINT)bufferLow.size() );
	}

	return streamInfo;
}

SVertexStreamInfo OvFileMeshLoader::_parseStreamMedium()
{
	SVertexStreamInfo streamInfo;
	medium_stream_buffer buffer;

	OliveValue::Integer vertCount( _readLine() );
	buffer.reserve( vertCount.GetInteger() );
	for ( unsigned i = 0 ; i < (unsigned)vertCount.GetInteger() ; ++i )
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
			, (UINT)buffer.size() );
	}

	return streamInfo;
}

LPDIRECT3DINDEXBUFFER9 OvFileMeshLoader::_parseIndexStream()
{
	LPDIRECT3DINDEXBUFFER9	indexStream = NULL;
	OliveValue::Integer faceCount( _readLine() );
	face_buffer faceBuffer;

	faceBuffer.reserve( faceCount.GetInteger() );
	for ( size_t i = 0 ; i < (unsigned)faceCount.GetInteger() ; ++i)
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
			, (UINT)faceBuffer.size() );
	}
	return indexStream;
}