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
	// OvResourceManager���� ���� ���� �������̽�.
	friend class OvResourceManager;
	OvResourceSPtr _load_resource( const OvString& fileLocation );
};