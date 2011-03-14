#pragma once
#include "OvRefObject.h"

#ifdef _WINSOCK2API_
#include <winsock2.h>
#include <Windows.h>
#endif

OvREF_POINTER(OvSocket);
class OvSocket : public OvRefObject
{
	OvRTTI_DECL( OvSocket );
private:
	OvSocket();
	~OvSocket();
public:

	OvSocketSPtr Connect( const string& ip, OvUInt port );

private:
	SOCKET m_socket;
};