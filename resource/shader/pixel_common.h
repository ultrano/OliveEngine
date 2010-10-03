#include <OvPShaderConst.h>

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
	float4 depth	: TEXCOORD6;
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