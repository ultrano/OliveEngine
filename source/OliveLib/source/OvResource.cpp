#include "OvResource.h"
#include "OvResourceManager.h"

OvRTTI_IMPL(OvResource);
OvRTTI_IMPL(OvResourceLoader);

OvResource::OvResource()
{
	OvResourceManager::GetInstance()->_call_when_resource_created( this );
}

OvResource::~OvResource()
{
	OvResourceManager::GetInstance()->_call_when_resource_deleted( this );
}

OvResourceSPtr OvResourceLoader::_load_resource( const std::string& fileLocation )
{
	return Load( fileLocation );
}
//////////////////////////////////////////////////////////////////////////
//////////////////////////////////////////////////////////////////////////
//////////////////////////////////////////////////////////////////////////

std::string OvResourceLocation::sm_resourceFolder;

void OvResourceLocation::SetResourceFolder( const std::string& folder )
{
	sm_resourceFolder = folder;
}

OvResourceLocation::OvResourceLocation( const char* file )
: m_completedFileLocation( sm_resourceFolder + "/" + std::string( file ) )
{

}
OvResourceLocation::OvResourceLocation( const std::string& file )
: m_completedFileLocation( sm_resourceFolder + "/" + file )
{

}

OvResourceLocation::~OvResourceLocation()
{

}

const std::string& OvResourceLocation::GetCompletedFileLocation()
{
	return m_completedFileLocation;
}

OvResourceLocation::operator const std::string&()
{
	return m_completedFileLocation;
}