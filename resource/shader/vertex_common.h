#include <OvVShaderConst.h>

struct vertex_geometry
{
	float3 pos		: POSITION;
	float3 norm		: NORMAL;
	float3 tan		: TANGENT;
};

struct vertex_texcoord
{
	float2 tex0		: TEXCOORD0;
};

struct input_vertex
{
	vertex_geometry	geom;
	vertex_texcoord tex;
};


struct output_vertex
{
	vector pos		: POSITION;
	float3 norm		: TEXCOORD0;
	float2 tex0		: TEXCOORD1;
	float3 eye		: TEXCOORD2;
	float3 eye2pos	: TEXCOORD3;
	float3 light	: TEXCOORD4;
	float4 time		: TEXCOORD5;
	float4 depth	: TEXCOORD6;
};
