#pragma once
#include "OvResourceLoader.h"

class OvTextureLoader : public OvResourceLoader
{
	OvRTTI_DECL( OvTextureLoader );
public:
	virtual OvResourceSPtr Load( const std::string& fileLocation ) override ;
};