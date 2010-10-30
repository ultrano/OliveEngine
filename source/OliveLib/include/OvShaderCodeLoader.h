#pragma once
#include "OvResourceLoader.h"

class OvShaderCodeLoader : public OvResourceLoader
{
public:
	virtual OvResourceSPtr Load( const std::string& fileLocation );
};