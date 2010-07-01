
#define CONST_DECLARE_IN_SHADER
#include "OvMaterialVConst.h"
#undef CONST_DECLARE_IN_SHADER

struct vertex_stream_input
{
	float3 pos		: POSITION;
	float3 norm		: NORMAL;
};


struct vertex_stream_output
{
	vector pos		: POSITION;
	float3 norm		: TEXCOORD0;
};

void	Vmain( in vertex_stream_input input, out vertex_stream_output output )
{
	output.pos = mul( vector( input.pos, 1.0 ), Matrix_WorldViewProject );
};