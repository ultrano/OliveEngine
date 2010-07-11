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

	const string&	GetResourceLocation() const ;

private:
	string		m_fileLocation;
};

OvREF_POINTER(OvResourceLoader);
class OvResourceLoader : public OvRefBase
{
public:

	virtual OvResourceSPtr Load( const std::string& fileLocation ) = 0;

};