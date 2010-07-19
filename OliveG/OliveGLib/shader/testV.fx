
#include "OvMaterialVConst.h"

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
};

void	main( in input_vertex input, out output_vertex output )
{
	output.pos = mul( vector( input.geom.pos, 1.0 ), WorldViewProject );
	
	float3 lightdir;
	lightdir.x = sin( Time );
	lightdir.y = 0;
	lightdir.z = cos( Time );
	lightdir = normalize( lightdir );
	
	float3 norm = normalize( mul( input.geom.norm, World) );
	float3 tan = normalize( mul( input.geom.tan, World) );
	float3 binorm = normalize( cross( norm, tan) );
	
	output.norm = norm;
	output.light.x = dot( lightdir, tan );
	output.light.y = dot( lightdir, binorm );
	output.light.z = dot( lightdir, norm );
	
	output.tex0 = input.tex.tex0;
	output.eye = ViewPos;
	output.eye2pos = normalize( input.geom.pos - ViewPos );
};