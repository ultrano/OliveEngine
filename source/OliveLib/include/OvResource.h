#pragma once
#include "OvRefBase.h"
#include "OvBitFlags.h"


class OvResourceLocation : public OvMemObject
{
public:
	static void SetResourceFolder( const std::string& folder );
	OvResourceLocation( const char* file);
	OvResourceLocation( const std::string& file );
	~OvResourceLocation();

	operator const std::string& ();
	const std::string& GetCompletedFileLocation();

private:
	static std::string sm_resourceFolder;
	std::string m_completedFileLocation;
};

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
	// OvResourceManager만을 위한 접근 인터페이스.
	friend class OvResourceManager;
	OvResourceSPtr _load_resource( const std::string& fileLocation );
};