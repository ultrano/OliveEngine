#pragma once
#include "OvPixelShader.h"

class OvPixelShaderLoader : public OvResourceLoader
{
	OvRTTI_DECL(OvPixelShaderLoader);
public:
	virtual OvResourceSPtr Load( const std::string& fileLocation ) override;
};
