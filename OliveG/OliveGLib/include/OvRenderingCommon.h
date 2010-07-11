#pragma once
#include <vector>
#include <map>
#include <d3dx9.h>

struct SFaceIndex
{
	SFaceIndex():_1(0),_2(0),_3(0){};
	SFaceIndex(short s1, short s2, short s3):_1(s1),_2(s2),_3(s3){};
	short _1;
	short _2;
	short _3;
} ;

typedef std::vector< SFaceIndex > face_buffer;

struct SVertexStreamInfo
{
	SVertexStreamInfo(): vertexStream( NULL ), vertexStride( 0 ), streamOffset( 0 ){};
	LPDIRECT3DVERTEXBUFFER9 vertexStream;
	size_t	vertexStride;
	size_t	streamOffset;
};