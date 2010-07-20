#pragma once
#include "OvNextTermMaterial.h"

class OvNextTermMaterialLoader : public OvResourceLoader
{
public:
	virtual OvResourceSPtr Load( const std::string& fileLocation );
};