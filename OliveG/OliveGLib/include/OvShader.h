#pragma once
#include "OvResource.h"
#include "d3dx9.h"

OvREF_POINTER(OvShader);
class	OvShader : public OvResource
{
	OvRTTI_DECL(OvShader);
	friend class OvPixelShaderLoader;
	friend class OvVertexShaderLoader;
public:

	const std::string& GetEntryFuncName();

	const std::string& GetCompileVersion();

private:

	std::string m_entryFuncName;
	std::string m_compileVersion;
};
