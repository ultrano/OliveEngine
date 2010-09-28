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

std::string OvResourceFolder::sm_resourceFolder;

void OvResourceFolder::SetFolderRoute( const std::string& folder )
{
	sm_resourceFolder = folder;
}
const string& OvResourceFolder::GetFolderRoute()
{
	return sm_resourceFolder;
}

OvResourceFolder::OvResourceFolder( const char* file )
: m_completedFileLocation( sm_resourceFolder + "/" + std::string( file ) )
{

}
OvResourceFolder::OvResourceFolder( const std::string& file )
: m_completedFileLocation( sm_resourceFolder + "/" + file )
{

}

OvResourceFolder::~OvResourceFolder()
{

}

const std::string& OvResourceFolder::GetCompletedFileLocation()
{
	return m_completedFileLocation;
}

OvResourceFolder::operator const std::string&()
{
	return m_completedFileLocation;
}