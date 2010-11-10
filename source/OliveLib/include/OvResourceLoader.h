#pragma once
#include "OvObject.h"

OvREF_POINTER(OvResource);
OvREF_POINTER(OvResourceLoader);
class OvDataStream;

class OvResourceLoader : public OvObject
{
	OvRTTI_DECL(OvResourceLoader);

	virtual OvResourceSPtr Load( OvDataStream& stream ) = 0;

private:
	// OvResourceManager���� ���� ���� �������̽�.
	friend class OvResourceManager;
	OvResourceSPtr _load_resource( const std::string& fileLocation );
};