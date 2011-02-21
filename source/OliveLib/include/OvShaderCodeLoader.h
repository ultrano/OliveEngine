#pragma once
#include "OvResourceLoader.h"

class OvShaderCodeLoader : public OvResourceLoader
{
	OvRTTI_DECL( OvShaderCodeLoader );
	OvFACTORY_OBJECT_DECL(OvShaderCodeLoader);
public:
	virtual OvResourceSPtr Load( OvBufferInputStream& bis ) override;
};