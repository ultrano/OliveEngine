
#include "OvMaterialPConst.h"



sampler SAMPLER_0	: register(s0);
sampler SAMPLER_1	: register(s1);

struct input_pixel
{
	float3 norm		: TEXCOORD0;
	float2 tex0		: TEXCOORD1;
	float3 eye		: TEXCOORD2;
	float3 eye2pos	: TEXCOORD3;
	float3 light	: TEXCOORD4;
	float4 time		: TEXCOORD5;
};

float4 texturesampler_0( float2 tex )
{
	return tex2D( SAMPLER_0, tex );	
};
float4 texturesampler_1( float2 tex )
{
	return tex2D( SAMPLER_1, tex );	
};

struct pixel_channel
{
	float4	diffuse;
	float3	normal;
	float4	emissive;
	float	specular_pow;
};

void main( in input_pixel input, out vector col0 : COLOR0 )
{
	pixel_channel output = (pixel_channel)0;

	// collecting channels
	output.diffuse		= texturesampler_0( input.tex0 );
	output.emissive		= texturesampler_0( input.tex0 ) / 2.0f;
	output.normal		= texturesampler_1( input.tex0 );
	output.specular_pow = 10;
	//
	
	// manufaturing channels
	
	output.normal = normalize( 2.0f * output.normal - 1.0f );
	
	float3 eye2pos	= normalize( input.eye2pos );
	float3 light	= normalize( input.light );

	float3 reflection = normalize( reflect( output.normal, eye2pos ) );

	float4 specular = max( 0, dot( light, reflection));
	col0 = output.emissive + ( output.diffuse * pow( specular, output.specular_pow) );
	
	//
	
}