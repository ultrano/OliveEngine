#include "OvResourceTicket.h"
#include "OvResource.h"
#include "OvResourceManager.h"

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