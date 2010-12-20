#pragma once
#include "OvResourceLoader.h"

class OvTextureLoader : public OvResourceLoader
{
	OvRTTI_DECL( OvTextureLoader );
	OvFACTORY_OBJECT_DECL(OvTextureLoader);
public:
	virtual OvResourceSPtr Load( OvDataStream& stream ) override ;
};