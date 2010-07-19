#pragma once
#include "OvVertexShader.h"

class OvVertexShaderLoader : public OvResourceLoader
{
	OvRTTI_DECL(OvVertexShaderLoader);
public:
	virtual OvResourceSPtr Load( const std::string& fileLocation ) override;
};
