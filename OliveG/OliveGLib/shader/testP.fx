
#define CONST_DECLARE_IN_SHADER
#include "OvMaterialPConst.h"
#undef CONST_DECLARE_IN_SHADER

struct pixel_stream_input
{
	float3 norm		: TEXCOORD1;
};

void Pmain( in pixel_stream_input input, out vector col0 : COLOR0 )
{
	col0 = vector(Float_Test,1.0);
}