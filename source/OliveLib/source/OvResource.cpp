#include "OvResource.h"
#include "OvResourceManager.h"

OvRTTI_IMPL(OvResource);
OvRTTI_IMPL(OvResourceLoader);

OvResource::OvResource()
{
	OvResourceManager::GetInstance()->_called_when_resource_created( this );
}

OvResource::~OvResource()
{
	OvResourceManager::GetInstance()->_called_when_resource_deleted( this );
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

OvResourceTicket::OvResourceTicket( const string& file )
: m_resource( NULL )
, m_fileName( file )
{
	OvResourceManager::GetInstance()->_called_when_ticket_created( this );
}

OvResourceTicket::~OvResourceTicket()
{
	OvResourceManager::GetInstance()->_called_when_ticket_deleted( this );
	m_resource = NULL;
}

OvResourceSPtr OvResourceTicket::CheckOut()
{
	return m_resource;
}

void OvResourceTicket::_check_in( OvResource* resource )
{
	m_resource = resource;
}

const string& OvResourceTicket::GetFileName()
{
	return m_fileName;
}