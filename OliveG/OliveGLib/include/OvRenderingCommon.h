#pragma once
#include "OvPoint3.h"
#include <vector>
#include <map>
#include <d3dx9.h>

class OvPoint3;
typedef struct _indecies_element
{
	_indecies_element():_1(0),_2(0),_3(0){};
	_indecies_element(short s1, short s2, short s3):_1(s1),_2(s2),_3(s3){};
	short _1;
	short _2;
	short _3;
} face_element;

typedef struct stream_0_element
{
	stream_0_element()
		: position( OvPoint3() )
		, normal( OvPoint3() )
	{
	};
	stream_0_element(const OvPoint3& pos, const OvPoint3& norm)
		: position( pos )
		, normal( norm )
	{
	};
	OvPoint3 position;
	OvPoint3 normal;
} geometry_element;

struct SBufferInfo
{
	SBufferInfo()
		:stream(0)
		,elemSize(0)
		,elemType(0)
		,elemUsage(0)
		,buffer(0)
		,elemCount(0)
	{
	};

	WORD stream;
	WORD elemSize;
	BYTE elemType;
	BYTE elemUsage;
	void* buffer;
	size_t elemCount;
};

struct SVertexStreamInfo
{
	LPDIRECT3DVERTEXBUFFER9 vertStream;
	size_t	vertStride;
};
typedef std::map<int,SVertexStreamInfo> stream_source_table;

struct SStreamInfo
{
	SStreamInfo()
		: faceStream( NULL )
		, vertDecl(NULL)
		, vertexCount(0)
		, faceCount(0)
	{};
	stream_source_table		vertStreamTable;
	LPDIRECT3DINDEXBUFFER9	faceStream;
	LPDIRECT3DVERTEXDECLARATION9 vertDecl;
	size_t	vertexCount;
	size_t	faceCount;
};

typedef std::vector< geometry_element > geometry_element_buffer;
typedef std::vector< face_element >		face_element_buffer;
typedef std::vector< OvPoint3 >			point3_buffer;

typedef std::vector<SBufferInfo>	stream_source_info_array;
typedef std::map< BYTE, BYTE >			usage_overlap_count_table;