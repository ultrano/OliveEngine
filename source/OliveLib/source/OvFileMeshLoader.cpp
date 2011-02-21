#include "OvFileMeshLoader.h"
#include "OvRenderer.h"
#include "OliveValue.h"
#include "OvPoint2.h"
#include "OvPoint3.h"
#include "OvBufferInputStream.h"
#include "OvBuffer.h"
#include "OvUtility.h"

OvRTTI_IMPL(OvFileMeshLoader);
OvFACTORY_OBJECT_IMPL(OvFileMeshLoader);
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
	m_buf.clear();
}

OvResourceSPtr OvFileMeshLoader::Load( OvBufferInputStream& bis )
{
	OvBufferSPtr buf = bis.GetBuffer();
	m_buf = (const char*)buf->Pointer();

	SVertexStreamInfo streamInfoLow;
	SVertexStreamInfo streamInfoMedium;
	SVertexStreamInfo streamInfoHigh;
	LPDIRECT3DINDEXBUFFER9	  streamFace = NULL;

	OvUInt vertexCount = Ov::FromString<OvInt>( _readLine() );
	OvUInt faceCount = Ov::FromString<OvInt>( _readLine() );
	streamInfoLow = _parseStreamLow();
	streamInfoMedium = _parseStreamMedium();
	streamFace = _parseIndexStream();

	return _buildMesh
		( streamInfoLow
		, streamInfoMedium
		, streamInfoHigh
		, OvRenderer::GetInstance()->CreateVertexDeclaration( MESH_ELEMENT )
		, vertexCount
		, streamFace
		, faceCount );

}


const OvChar* OvFileMeshLoader::_readLine()
{
	// fgets() 의 특성상 '\n' 개행 문자가 끌려 온다.
	// 개행 문자가 있으면 문자를 다른 데이터타입으로 변환시 
	// 문제가 발생할수 있으므로 '\0'터미널 문자로 바꿔준다.
	m_readBuffer = OU::string::split( m_buf, "\n");
	return m_readBuffer.c_str();
}

SVertexStreamInfo OvFileMeshLoader::_parseStreamLow()
{
	low_stream_buffer bufferLow;

	vector< OvPoint3 > posBuffer;
	vector< OvPoint3 > normBuffer;
	vector< OvPoint3 > tanBuffer;

	OvUInt vertNum = Ov::FromString<OvInt>( _readLine() );
	posBuffer.reserve( vertNum );
	for ( unsigned i = 0 ; i < (unsigned)vertNum ; ++i )
	{
		OvPoint3 pos = Ov::FromString<OvPoint3>( _readLine() );
		posBuffer.push_back( pos );
	}

	normBuffer.reserve( vertNum );
	for ( unsigned i = 0 ; i < (unsigned)vertNum ; ++i )
	{
		OvPoint3 norm = Ov::FromString<OvPoint3>( _readLine() );
		normBuffer.push_back( norm );
	}

	tanBuffer.reserve( vertNum );
	for ( unsigned i = 0 ; i < (unsigned)vertNum ; ++i )
	{
		OvPoint3 tan = Ov::FromString<OvPoint3>( _readLine() );
		tanBuffer.push_back( tan );
	}

	bufferLow.reserve( vertNum );
	for ( unsigned i = 0 ; i < (unsigned)vertNum ; ++i )
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

	OvUInt vertCount = Ov::FromString<OvInt>( _readLine() );
	buffer.reserve( vertCount );
	for ( unsigned i = 0 ; i < (unsigned)vertCount ; ++i )
	{
		OvPoint2 tvert = Ov::FromString<OvPoint2>( _readLine() );
		SVertex_Medium vertex;
		vertex.tex0 = tvert;
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
	OvUInt faceCount = Ov::FromString<OvInt>( _readLine() );
	face_buffer faceBuffer;

	faceBuffer.reserve( faceCount );
	for ( size_t i = 0 ; i < (unsigned)faceCount ; ++i)
	{
		OvPoint3 readIndex = Ov::FromString<OvPoint3>( _readLine() );
		OvPoint3 findex3 = readIndex;
		faceBuffer.push_back( SFaceIndex( (OvShort)findex3.x, (OvShort)findex3.y, (OvShort)findex3.z ) );
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