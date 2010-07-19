#include "OvPixelShaderLoader.h"
#include "OvShaderManager.h"
#include <iostream>
#include <fstream>

OvRTTI_IMPL(OvPixelShaderLoader);

OvResourceSPtr OvPixelShaderLoader::Load( const std::string& fileLocation )
{
	ifstream file( fileLocation.c_str() );

	OvPixelShaderSPtr shader = NULL;
	if ( file.is_open() )
	{
		string directory = OvGetDirectoryInFullFilePath( fileLocation );

		string shader_code_file;
		string entry_function;
		string compile_version;

		file >> shader_code_file;
		file >> entry_function;
		file >> compile_version;

		string code_location = directory + shader_code_file;

		LPDIRECT3DPIXELSHADER9 directShader = OvShaderManager::GetInstance()->CreatePixelShaderFromFile
			( code_location
			, entry_function
			, compile_version);

		if ( directShader )
		{
			shader = OvNew OvPixelShader( directShader );
			shader->m_entryFuncName = entry_function;
			shader->m_compileVersion = compile_version;
		}
	}
	return shader;
}