
#define CONST_DECLARE_IN_SHADER
#include "OvMaterialVConst.h"
#undef CONST_DECLARE_IN_SHADER

struct vertex_stream_input
{
	float3 pos		: POSITION;
	float3 norm		: NORMAL;
	float3 tan		: TANGENT;
	float2 tex0		: TEXCOORD0;
};


struct vertex_stream_output
{
	vector pos		: POSITION;
	float3 norm		: TEXCOORD0;
	float2 tex0		: TEXCOORD1;
	float3 eye		: TEXCOORD2;
	float3 eye2pos	: TEXCOORD3;
	float3 light	: TEXCOORD4;
};

void	Vmain( in vertex_stream_input input, out vertex_stream_output output )
{
	output.pos = mul( vector( input.pos, 1.0 ), WorldViewProject );
	
	float3 lightdir;
	lightdir.x = 0;
	lightdir.y = sin( Time );
	lightdir.z = cos( Time );
	lightdir = normalize( lightdir );
	
	float3 norm = normalize( mul( input.norm, World) );
	float3 tan = normalize( mul( input.tan, World) );
	float3 binorm = normalize( cross( norm, tan) );
	
	output.norm = norm;
	output.light.x = dot( lightdir, tan );
	output.light.y = dot( lightdir, binorm );
	output.light.z = dot( lightdir, norm );
	
	output.tex0 = input.tex0;
	output.eye = ViewPos;
	output.eye2pos = normalize( input.pos - ViewPos );
};