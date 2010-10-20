#include "OvShaderCodeLoader.h"

OvResourceSPtr OvShaderCodeLoader::Load( const std::string& fileLocation )
{

	FILE* file = NULL;
	fopen_s( &file, fileLocation.c_str(), "r" );

	if ( file )
	{
		string shader_code;
		char line[256]={0};
		while ( fgets( line, 256, file ) )
		{
			shader_code += line;
		}
		fclose( file );
		return new OvShaderCode( shader_code );
	}

	return NULL;
}