
#include <pixel_common.h>



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