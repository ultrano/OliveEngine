#pragma once
#include "OvRefBase.h"

OvREF_POINTER(OvResource);
OvREF_POINTER(OvResourceTicket);
class OvResourceTicket : public OvRefBase
{
	friend class OvResourceManager;
public:
	~OvResourceTicket();

	OvResourceSPtr CheckOut();

	const OvRTTI*	GetResourceType();
	const string&	GetFileName();

private:

	OvResourceTicket( const OvRTTI* type, const string& file );
	void _check_in( OvResource* resource );

private:
	OvResourceSPtr	m_resource;
	const OvRTTI*	m_resourceType;
	std::string		m_fileName;
	CRITICAL_SECTION m_section;
};