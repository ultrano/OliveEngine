#pragma once
#include "OvResource.h"
#include <string>
#include <map>

OvREF_POINTER(OvShader);
OvREF_POINTER(OvVertexShader);
OvREF_POINTER(OvPixelShader);
OvREF_POINTER(OvShaderCode);
class OvShaderCode : public OvResource
{
	OvRTTI_DECL( OvShaderCode );
	typedef std::map< std::pair<std::string,std::string>, OvShaderSPtr > precompiled_shader_table;
public:
	
	OvShaderCode( const std::string& code);
	const string&	GetCodeString();
	void*			GetCodeBuffer();
	size_t			GetCodeSize();

	OvVertexShaderSPtr	CreateVertexShader( const std::string& entry_func, const std::string& compile_version );
	OvPixelShaderSPtr	CreatePixelShader( const std::string& entry_func, const std::string& compile_version );

private:

	OvShaderSPtr	_find_precompiled_shader( const std::string& entry_func, const std::string& compile_version );
	void			_register_compiled_shader( const std::string& entry_func, const std::string& compile_version, OvShaderSPtr compiled_shader );

private:
	string m_code;
	precompiled_shader_table	m_precompiledShaderTable;
};