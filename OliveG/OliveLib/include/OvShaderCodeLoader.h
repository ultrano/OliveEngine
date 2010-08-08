#pragma once
#include "OvShaderCode.h"

class OvShaderCodeLoader : public OvResourceLoader
{
public:
	virtual OvResourceSPtr Load( const std::string& fileLocation );
};