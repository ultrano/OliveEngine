#pragma once
#include "OvPoint3.h"
#include <vector>
#include <map>
#include <d3dx9.h>

class OvPoint3;

//////////////////////////////////////////////////////////////////////////
//////////////////////////////////////////////////////////////////////////
//////////////////////////////////////////////////////////////////////////
//////////////////////////////////////////////////////////////////////////
//////////////////////////////////////////////////////////////////////////

typedef struct SSIndexElement
{
	SSIndexElement():_1(0),_2(0),_3(0){};
	SSIndexElement(short s1, short s2, short s3):_1(s1),_2(s2),_3(s3){};
	short _1;
	short _2;
	short _3;
} face_element;

typedef vector< face_element > face_element_buffer;

typedef struct SStream0Element
{
	SStream0Element()
		: position( OvPoint3() )
		, normal( OvPoint3() )
	{
	};
	SStream0Element(const OvPoint3& pos, const OvPoint3& norm)
		: position( pos )
		, normal( norm )
	{
	};
	OvPoint3 position;
	OvPoint3 normal;
} stream_0_element;

typedef vector< stream_0_element > stream_0_element_buffer;

struct SVertexStreamInfo
{
	LPDIRECT3DVERTEXBUFFER9 vertexStream;
	size_t	vertexStride;
};
typedef map<int,SVertexStreamInfo>	vertex_stream_table;

enum eVertStreamIndex
{
	Pos_Norm,
};

D3DVERTEXELEMENT9 MESH_VERT_ELEMENT[] =
{
	{ Pos_Norm, 0
	, D3DDECLTYPE_FLOAT3
	, D3DDECLMETHOD_DEFAULT
	, D3DDECLUSAGE_POSITION, 0 },

	{ Pos_Norm, 12
	, D3DDECLTYPE_FLOAT3
	, D3DDECLMETHOD_DEFAULT
	, D3DDECLUSAGE_POSITION,0},

	D3DDECL_END()
};

struct SRenderData
{
	vertex_stream_table	vertStreamTable;
	LPDIRECT3DINDEXBUFFER9	faceStream;
	LPDIRECT3DVERTEXDECLARATION9 vertDecl;
	size_t	vertexCount;
	size_t	faceCount;
};