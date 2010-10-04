#include "OvShaderCode.h"
#include "OvVertexShader.h"
#include "OvPixelShader.h"
#include "OvShaderCodeIncluder.h"
#include "OvRenderer.h"
#include <d3dx9.h>
using namespace std;
OvRTTI_IMPL( OvShaderCode );

//////////////////////////////////////////////////////////////////////////
struct SDxAutoRelease
{
	SDxAutoRelease( IUnknown* target ):m_target( target ){};
	~SDxAutoRelease(){if(m_target)m_target->Release();};

	IUnknown* m_target;
};
//////////////////////////////////////////////////////////////////////////

LPD3DXBUFFER	CompileShaderFromCode( const string& code, const string& funcName, const string& version, LPD3DXINCLUDE includer = NULL)
{
	LPD3DXBUFFER	shaderBuffer = NULL;
	LPD3DXBUFFER	compileResult = NULL;
	HRESULT hr = D3DXCompileShader
		( code.c_str()
		, code.size()
		, NULL
		, includer
		, funcName.c_str()
		, version.c_str()
		, D3DXSHADER_DEBUG
		, &shaderBuffer
		, &compileResult
		, NULL);
	if ( SUCCEEDED( hr ) )
	{
		return shaderBuffer;
	}
	else
	{
		SDxAutoRelease autoRelease0( compileResult );
		SDxAutoRelease autoRelease1( shaderBuffer );
		if ( compileResult )
		{
			OvAssertMsg( ( char* )compileResult->GetBufferPointer() );
		}
		return NULL;
	}
	return NULL;
}
//////////////////////////////////////////////////////////////////////////
//////////////////////////////////////////////////////////////////////////
//////////////////////////////////////////////////////////////////////////

OvShaderCode::OvShaderCode( const string& code )
: m_code( code )
{

}

const string& OvShaderCode::GetCodeString()
{
	return m_code;
}

void* OvShaderCode::GetCodeBuffer()
{
	return &( m_code[ 0 ] );
}

size_t OvShaderCode::GetCodeSize()
{
	return m_code.size();
}

OvVertexShaderSPtr OvShaderCode::CreateVertexShader( const string& entry_func, const string& compile_version )
{
	OvShaderCodeIncluder includer;
	OvVertexShaderSPtr outShader = _find_precompiled_shader( entry_func, compile_version );
	if ( outShader == NULL )
	{
		LPD3DXBUFFER shaderBuffer = CompileShaderFromCode( m_code, entry_func, compile_version, &includer );
		SDxAutoRelease autoRelease( shaderBuffer );
		if ( shaderBuffer )
		{
			LPDIRECT3DDEVICE9 device = OvRenderer::GetInstance()->GetDevice();
			if ( device )
			{
				LPDIRECT3DVERTEXSHADER9 shader = NULL;
				if ( SUCCEEDED( device->CreateVertexShader( (DWORD*)shaderBuffer->GetBufferPointer(), &shader ) ) )
				{
					outShader = OvNew OvVertexShader( shader );
					_register_compiled_shader( entry_func, compile_version, outShader );
				}
			}
		}
	}
	return outShader;
}
OvPixelShaderSPtr	OvShaderCode::CreatePixelShader( const string& entry_func, const string& compile_version )
{
	OvShaderCodeIncluder includer;
	OvPixelShaderSPtr outShader = _find_precompiled_shader( entry_func, compile_version );
	if ( outShader == NULL )
	{
		LPD3DXBUFFER shaderBuffer = CompileShaderFromCode( m_code, entry_func, compile_version, &includer );
		SDxAutoRelease autoRelease( shaderBuffer );
		if ( shaderBuffer )
		{
			LPDIRECT3DDEVICE9 device = OvRenderer::GetInstance()->GetDevice();
			if ( device )
			{
				LPDIRECT3DPIXELSHADER9 shader = NULL;
				if ( SUCCEEDED( device->CreatePixelShader( (DWORD*)shaderBuffer->GetBufferPointer(), &shader ) ) )
				{
					outShader = OvNew OvPixelShader( shader );
					_register_compiled_shader( entry_func, compile_version, outShader );
				}
			}
		}
	}
	return outShader;
}

OvShaderSPtr OvShaderCode::_find_precompiled_shader( const std::string& entry_func, const std::string& compile_version )
{
	OvShaderSPtr precompiled_shader = NULL;
	
	precompiled_shader_table::key_type search_key( entry_func, compile_version );
	
	precompiled_shader_table::iterator itor = m_precompiledShaderTable.find( search_key );

	if ( m_precompiledShaderTable.end() != itor )
	{
		precompiled_shader = itor->second;
	}

	return precompiled_shader;
}

void OvShaderCode::_register_compiled_shader( const std::string& entry_func, const std::string& compile_version, OvShaderSPtr compiled_shader )
{
	precompiled_shader_table::key_type key( entry_func, compile_version );
	precompiled_shader_table::value_type table_value( key, compiled_shader );
	m_precompiledShaderTable.insert( table_value );
}
//////////////////////////////////////////////////////////////////////////
//////////////////////////////////////////////////////////////////////////
