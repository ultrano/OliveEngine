#pragma once
#include "OvResourceLoader.h"
class OvMaterialLoader : public OvResourceLoader
{
	OvRTTI_DECL( OvMaterialLoader );
	OvFACTORY_OBJECT_DECL(OvMaterialLoader);
public:
	virtual OvResourceSPtr Load( OvDataStream& stream );
};