#pragma once
#include "OvObject.h"

OvREF_POINTER(OvResource);
OvREF_POINTER(OvResourceLoader);

class OvResourceLoader : public OvObject
{
	OvRTTI_DECL(OvResourceLoader);

	virtual OvResourceSPtr Load( const std::string& fileLocation ) = 0;

private:
	// OvResourceManager만을 위한 접근 인터페이스.
	friend class OvResourceManager;
	OvResourceSPtr _load_resource( const std::string& fileLocation );
};