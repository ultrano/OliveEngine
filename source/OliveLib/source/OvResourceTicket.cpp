#include "OvResourceTicket.h"
#include "OvResource.h"
#include "OvResourceManager.h"

OvResourceTicket::OvResourceTicket( const OvRTTI* type, const string& file )
: m_resource( NULL )
, m_resourceType( type )
, m_fileName( file )
{
	::InitializeCriticalSection( &m_section );
	OvResourceManager::GetInstance()->_called_when_ticket_created( this );
}

OvResourceTicket::~OvResourceTicket()
{
	::DeleteCriticalSection( &m_section );
	OvResourceManager::GetInstance()->_called_when_ticket_deleted( this );
	m_resource = NULL;
}

OvResourceSPtr OvResourceTicket::CheckOut()
{
	OvSectionGuardian guardian( m_section );
	return m_resource;
}

void OvResourceTicket::_check_in( OvResource* resource )
{
	OvSectionGuardian guardian( m_section );
	m_resource = resource;
}

const OvRTTI* OvResourceTicket::GetResourceType()
{
	return m_resourceType;
}

const string& OvResourceTicket::GetFileName()
{
	return m_fileName;
}