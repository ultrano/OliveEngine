#pragma once
#include "OvRefObject.h"

OvREF_POINTER(OvSocket);
class OvSocket : public OvRefObject
{
	OvRTTI_DECL( OvSocket );
private:
	OvSocket();
	~OvSocket();
public:

	static OvSocketSPtr Connect( const string& ip, OvUInt port );

public:

	void	Close();

private:
	SOCKET m_socket;
};