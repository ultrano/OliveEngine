#pragma once
#include "OvResource.h"
#include <map>

OvREF_POINTER(OvShader);
OvREF_POINTER(OvVertexShader);
OvREF_POINTER(OvPixelShader);
OvREF_POINTER(OvShaderCode);
class OvShaderCode : public OvResource
{
	OvRTTI_DECL( OvShaderCode );
	typedef std::map< std::pair<OvString,OvString>, OvShaderSPtr > precompiled_shader_table;
public:

	OvShaderCode( const OvString& code);
	const string&	GetCodeString();
	void*			GetCodeBuffer();
	size_t			GetCodeSize();

	OvVertexShaderSPtr	CompileVertexShader( const OvString& entry_func, const OvString& compile_version );
	OvPixelShaderSPtr	CompilePixelShader( const OvString& entry_func, const OvString& compile_version );

	OvShaderSPtr	FindShader( const OvString& entry_func, const OvString& compile_version );

	void			RefreshShader( OvShaderSPtr shader );
private:

	OvShaderSPtr	_find_precompiled_shader( const OvString& entry_func, const OvString& compile_version );
	void			_register_compiled_shader( const OvString& entry_func, const OvString& compile_version, OvShaderSPtr compiled_shader );

private:
	string m_code;
	precompiled_shader_table	m_precompiledShaderTable;
};