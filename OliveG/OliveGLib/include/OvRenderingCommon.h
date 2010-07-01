#pragma once
#include <vector>
#include <map>
#include <d3dx9.h>

typedef struct SSIndexElement
{
	SSIndexElement():_1(0),_2(0),_3(0){};
	SSIndexElement(short s1, short s2, short s3):_1(s1),_2(s2),_3(s3){};
	short _1;
	short _2;
	short _3;
} index_element;

typedef std::vector< index_element > index_buffer;


struct SVertexStreamInfo
{
	LPDIRECT3DVERTEXBUFFER9 vertexStream;
	size_t	vertexStride;
	size_t	streamOffset;
};
typedef std::map<WORD,SVertexStreamInfo>	vertex_stream_table;


struct SRenderData
{
	vertex_stream_table	vertStreamTable;
	LPDIRECT3DINDEXBUFFER9	faceStream;
	LPDIRECT3DVERTEXDECLARATION9 vertDecl;
	size_t	vertexCount;
	size_t	faceCount;
};