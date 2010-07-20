#include "OvShaderCodeIncluder.h"
#include "OvGlobalFunc.h"
#include <iostream>
#include <fstream>
using namespace std;


OvShaderCodeIncluder::OvShaderCodeIncluder( const std::string& basePath )
: m_basePath( basePath )
{

}

STDMETHODIMP OvShaderCodeIncluder::Open( THIS_ D3DXINCLUDE_TYPE IncludeType, LPCSTR pFileName, LPCVOID pParentData, LPCVOID *ppData, UINT *pBytes )
{
	if ( D3DXINC_SYSTEM == IncludeType )
	{
		string fileLocation = m_basePath + "/" + pFileName;

		FILE* file = fopen( fileLocation.c_str(), "r" );

		string shader_code;
		if ( file )
		{
			char line[256]={0};
			while ( fgets( line, 256, file ) )
			{
				shader_code += line;
			}
			OvMessageBox( shader_code.c_str(), "");
			char* data = new char[ shader_code.size() ];
			memcpy( data, shader_code.c_str(), shader_code.size() );
			*ppData = data;
			*pBytes = shader_code.size();
		}
		return S_OK;
	}
}

STDMETHODIMP OvShaderCodeIncluder::Close( THIS_ LPCVOID pData )
{
	if ( pData )
	{
		delete pData;
	}
	return S_OK;
}