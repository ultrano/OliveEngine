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
	const OvString&	GetFileName();

private:

	OvResourceTicket( const OvRTTI* type, const OvString& file );
	void _check_in( OvResource* resource );

private:
	OvResourceSPtr		m_resource;
	const OvRTTI*		m_resourceType;
	const OvString&	m_fileName;
};