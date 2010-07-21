#include <vertex_common.h>

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