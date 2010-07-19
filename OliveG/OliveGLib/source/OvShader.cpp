#include "OvShader.h"
OvRTTI_IMPL(OvShader);

const std::string& OvShader::GetEntryFuncName()
{
	return m_entryFuncName;
}

const std::string& OvShader::GetCompileVersion()
{
	return m_compileVersion;
}
