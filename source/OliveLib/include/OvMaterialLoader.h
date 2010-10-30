#pragma once
#include "OvResourceLoader.h"
class OvMaterialLoader : public OvResourceLoader
{
public:
	virtual OvResourceSPtr Load( const std::string& fileLocation );
};