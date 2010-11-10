#pragma once
#include "OvResourceLoader.h"

class OvShaderCodeLoader : public OvResourceLoader
{
	OvRTTI_DECL( OvShaderCodeLoader );
public:
	virtual OvResourceSPtr Load( OvDataStream& stream );
};