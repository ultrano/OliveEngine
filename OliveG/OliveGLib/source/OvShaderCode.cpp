#include "OvShaderCode.h"
OvRTTI_IMPL( OvShaderCode );

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