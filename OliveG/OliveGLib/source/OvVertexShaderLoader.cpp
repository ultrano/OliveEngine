#include "OvVertexShaderLoader.h"
#include "OvShaderManager.h"
#include <iostream>
#include <fstream>

OvRTTI_IMPL(OvVertexShaderLoader);

OvResourceSPtr OvVertexShaderLoader::Load( const std::string& fileLocation )
{

	ifstream file( fileLocation.c_str() );

	OvVertexShaderSPtr shader = NULL;
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

		LPDIRECT3DVERTEXSHADER9 directShader = OvShaderManager::GetInstance()->CreateVertexShaderFromFile
			( code_location
			, entry_function
			, compile_version);

		if ( directShader )
		{
			shader = OvNew OvVertexShader( directShader );
			shader->m_entryFuncName = entry_function;
			shader->m_compileVersion = compile_version;
		}
	}
	return shader;
}