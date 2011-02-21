#include "OvShaderCode.h"
#include "OvVertexShader.h"
#include "OvPixelShader.h"
#include "OvShaderCodeIncluder.h"
#include "OvRenderer.h"
#include "OvUtility.h"
#include "OvGlobalFunc.h"
#include "OvMacro.h"
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

LPD3DXBUFFER	CompileShaderFromCode( const OvString& code, const OvString& funcName, const OvString& version, LPD3DXINCLUDE includer = NULL)
{
	LPD3DXBUFFER	shaderBuffer = NULL;
	LPD3DXBUFFER	compileResult = NULL;
	HRESULT hr = D3DXCompileShader
		( code.c_str()
		, (UINT)code.size()
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
			OvError( ( OvChar* )compileResult->GetBufferPointer() );
		}
		return NULL;
	}
	return NULL;
}
//////////////////////////////////////////////////////////////////////////
//////////////////////////////////////////////////////////////////////////
//////////////////////////////////////////////////////////////////////////

OvShaderCode::OvShaderCode( const OvString& code )
: m_code( code )
{

}

OvShaderCode::OvShaderCode( const OvChar* buf, OvSize size )
{
	if ( buf && size )
	{
		m_code.resize( size );
		memcpy( &m_code[0], buf, size );
	}
}

const OvString& OvShaderCode::GetCodeString()
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

OvVertexShaderSPtr OvShaderCode::CompileVertexShader( const OvString& entry_func, const OvString& compile_version )
{
	OvShaderCodeIncluder includer;
	OvVertexShaderSPtr outShader = _find_precompiled_shader( entry_func, compile_version );
	if ( outShader == NULL )
	{
		LPD3DXBUFFER shaderBuffer = CompileShaderFromCode( m_code, entry_func, compile_version, &includer );
		SDxAutoRelease autoRelease( shaderBuffer );
		if ( shaderBuffer )
		{
			OvDevice device = OvRenderer::GetInstance()->GetDevice();
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
OvPixelShaderSPtr	OvShaderCode::CompilePixelShader( const OvString& entry_func, const OvString& compile_version )
{
	OvShaderCodeIncluder includer;
	OvPixelShaderSPtr outShader = _find_precompiled_shader( entry_func, compile_version );
	if ( outShader == NULL )
	{
		LPD3DXBUFFER shaderBuffer = CompileShaderFromCode( m_code, entry_func, compile_version, &includer );
		SDxAutoRelease autoRelease( shaderBuffer );
		if ( shaderBuffer )
		{
			OvDevice device = OvRenderer::GetInstance()->GetDevice();
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

OvShaderSPtr OvShaderCode::FindShader( const OvString& entry_func, const OvString& compile_version )
{
	OvShaderSPtr precompiled_shader = _find_precompiled_shader( entry_func, compile_version );
	if ( NULL == precompiled_shader )
	{
		OvString err = OU::string::format("[func: %s, compile_version: %s] can't found, maybe not complied"
			,entry_func.c_str()
			, compile_version.c_str() );
		OvError( err.c_str() );
	}
	return precompiled_shader;
}

OvShaderSPtr OvShaderCode::_find_precompiled_shader( const OvString& entry_func, const OvString& compile_version )
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

void OvShaderCode::_register_compiled_shader( const OvString& entry_func, const OvString& compile_version, OvShaderSPtr compiled_shader )
{
	precompiled_shader_table::key_type key( entry_func, compile_version );
	precompiled_shader_table::value_type table_value( key, compiled_shader );
	m_precompiledShaderTable.insert( table_value );
}
//////////////////////////////////////////////////////////////////////////
//////////////////////////////////////////////////////////////////////////
