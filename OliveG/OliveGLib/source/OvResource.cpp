#include "OvResource.h"
#include "OvResourceManager.h"

OvRTTI_IMPL(OvResource);
OvRTTI_IMPL(OvResourceLoader);

OvResource::OvResource()
{
}

OvResource::~OvResource()
{
	OvResourceManager::GetInstance()->_resource_deleted( this );
}

void OvResource::SetFileLocation( const string& file )
{
	m_fileLocation = file;
}
const string& OvResource::GetFileLocation() const
{
	return m_fileLocation;
}