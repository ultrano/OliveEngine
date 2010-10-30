#pragma once
#include "OvResourceLoader.h"

class OvTextureLoader : public OvResourceLoader
{
public:
	virtual OvResourceSPtr Load( const std::string& fileLocation ) override ;
};