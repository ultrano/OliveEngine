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

	const string&	GetFileName();

private:

	OvResourceTicket( const string& file );
	void _check_in( OvResource* resource );

private:
	OvResourceSPtr m_resource;
	std::string m_fileName;
};