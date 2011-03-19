#pragma once
#include "OvRefObject.h"

OvREF_POINTER(OvSocket);
class OvSocket : public OvRefObject
{
	OvRTTI_DECL( OvSocket );
	struct Address
	{
		OvString ip;
		OvShort	 port;
	};
private:
	OvSocket();
	~OvSocket();
public:

	static OvBool Startup();
	static OvBool Cleanup();

	static OvSocketSPtr Connect( const string& ip, OvUInt port );
	static OvSocketSPtr Bind( const OvString& ip, OvUInt port );

public:

	OvBool GetPeerAddr( Address& addr );
	OvBool GetSockAddr( Address& addr );

	void	Close();

private:
	SOCKET m_socket;
};