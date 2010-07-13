
#define CONST_DECLARE_IN_SHADER
#include "OvMaterialPConst.h"
#undef CONST_DECLARE_IN_SHADER



sampler SAMPLER_DIFFUSE	: register(s0);
sampler SAMPLER_NORMAL	: register(s1);

struct pixel_stream_input
{
	float3 norm		: TEXCOORD0;
	float2 tex0		: TEXCOORD1;
	float3 eye		: TEXCOORD2;
	float3 eye2pos	: TEXCOORD3;
	float3 light	: TEXCOORD4;
};

void Pmain( in pixel_stream_input input, out vector col0 : COLOR0 )
{
	
	float3 texnorm = normalize( 2.0f * tex2D( SAMPLER_NORMAL, input.tex0).xyz - 1.0f );
	float3 eye2pos = normalize( input.eye2pos );
	float3 light = normalize( input.light );

	float3 reflection = normalize( reflect( texnorm, eye2pos ) );
	reflection = normalize( reflection );

	col0 = max( 0, dot( light, reflection));
	col0 += pow( col0, 50);

	float2 tex0 = input.tex0;
	col0 *= tex2D( SAMPLER_DIFFUSE, tex0 );
	
	
	
	
	//col0 = tex2D( SAMPLER_DIFFUSE, input.tex0 );
	//col0 = input.tex0.x;
}