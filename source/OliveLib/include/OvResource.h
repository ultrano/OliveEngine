#pragma once
#include "OvRefBase.h"
#include "OvBitFlags.h"

OvREF_POINTER(OvResource);
class OvResource : public OvRefBase
{
	OvRTTI_DECL(OvResource);
public:

	OvResource();
	~OvResource();

};

OvREF_POINTER(OvResourceLoader);
class OvResourceLoader : public OvRefBase
{
	OvRTTI_DECL(OvResourceLoader);

	virtual OvResourceSPtr Load( const std::string& fileLocation ) = 0;

private:
	// OvResourceManager���� ���� ���� �������̽�.
	friend class OvResourceManager;
	OvResourceSPtr _load_resource( const std::string& fileLocation );
};