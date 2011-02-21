#pragma once
#include "OvObject.h"

OvREF_POINTER(OvResource);
OvREF_POINTER(OvResourceLoader);
OvREF_POINTER(OvBufferInputStream);

class OvResourceLoader : public OvObject
{
	OvRTTI_DECL(OvResourceLoader);

	virtual OvResourceSPtr Load( OvBufferInputStream& bis ) = 0;

private:
	// OvResourceManager만을 위한 접근 인터페이스.
	friend class OvResourceManager;
	OvResourceSPtr _load_resource( const OvString& fileLocation );
};