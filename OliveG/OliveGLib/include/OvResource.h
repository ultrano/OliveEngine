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

	void	SetFileLocation(const string& file);
	const string&	GetFileLocation() const ;

private:
	string		m_fileLocation;
};

OvREF_POINTER(OvResourceLoader);
class OvResourceLoader : public OvRefBase
{
	OvRTTI_DECL(OvResourceLoader);
public:

	virtual OvResourceSPtr Load( const std::string& fileLocation ) = 0;

};