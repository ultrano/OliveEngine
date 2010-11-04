#pragma once
#include "OvResourceLoader.h"
class OvMaterialLoader : public OvResourceLoader
{
	OvRTTI_DECL( OvMaterialLoader );
public:
	virtual OvResourceSPtr Load( const std::string& fileLocation );
};