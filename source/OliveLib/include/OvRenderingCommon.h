#pragma once
#include <vector>
#include <map>
#include <d3dx9.h>

struct SFaceIndex
{
	SFaceIndex():_1(0),_2(0),_3(0){};
	SFaceIndex(OvShort s1, OvShort s2, OvShort s3):_1(s1),_2(s2),_3(s3){};
	OvShort _1;
	OvShort _2;
	OvShort _3;
} ;

typedef std::vector< SFaceIndex > face_buffer;

struct SVertexStreamInfo
{
	SVertexStreamInfo(): vertexStream( NULL ), vertexStride( 0 ), streamOffset( 0 ){};
	SVertexStreamInfo( 
		LPDIRECT3DVERTEXBUFFER9 _vertexStream,
		UINT	_vertexStride,
		UINT	_streamOffset)
		: vertexStream( _vertexStream )
		, vertexStride( _vertexStride )
		, streamOffset( _streamOffset ){};
	LPDIRECT3DVERTEXBUFFER9 vertexStream;
	UINT	vertexStride;
	UINT	streamOffset;
};