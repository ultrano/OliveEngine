#include "OvResourceTicket.h"
#include "OvResource.h"
#include "OvResourceManager.h"
#include "OvThreadSync.h"

OvResourceTicket::OvResourceTicket( const OvRTTI* type, const OvString& file )
: m_resource( NULL )
, m_resourceType( type )
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
	OvThreadSyncer<OvResourceTicket>::OvSectionLock lock;
	return m_resource;
}

void OvResourceTicket::_check_in( OvResource* resource )
{
	OvThreadSyncer<OvResourceTicket>::OvSectionLock lock;
	m_resource = resource;
}

const OvRTTI* OvResourceTicket::GetResourceType()
{
	OvThreadSyncer<OvResourceTicket>::OvSectionLock lock;
	return m_resourceType;
}

const OvString& OvResourceTicket::GetFileName()
{
	OvThreadSyncer<OvResourceTicket>::OvSectionLock lock;
	return m_fileName;
}