#include "OvSocket.h"

OvRTTI_IMPL( OvSocket );

OvSocket::OvSocket()
: m_socket( NULL )
{

}

OvSocket::~OvSocket()
{
	Close();
}

OvSocketSPtr OvSocket::Connect( const string& ip, OvUInt port )
{
	OvSocketSPtr ovsocket = NULL;
	SOCKET sock = socket( AF_INET, SOCK_STREAM, 0 );
	if ( INVALID_SOCKET != sock )
	{
		SOCKADDR_IN add_in;
		add_in.sin_family = AF_INET;
		add_in.sin_port = htons( port );
		add_in.sin_addr.s_addr = inet_addr( ip.c_str() );

		if ( SOCKET_ERROR != connect( sock, (SOCKADDR*)&add_in, sizeof(add_in) ) )
		{
			ovsocket = OvNew OvSocket;
			ovsocket->m_socket = sock;
		}
	}
	return ovsocket;
}

void OvSocket::Close()
{
	if ( m_socket )
	{
		closesocket( m_socket );
		m_socket = NULL;
	}
}

OvSocketSPtr OvSocket::Bind( const OvString& ip, OvUInt port )
{
	SOCKET sock = socket( AF_INET, SOCK_STREAM, 0 );

	OvUInt addr = ( ip == "*" )? INADDR_ANY : inet_addr( ip.c_str() );
	SOCKADDR_IN addr_in;
	addr_in.sin_family = AF_INET;
	addr_in.sin_port = htons( port );
	addr_in.sin_addr.s_addr = addr;

	if ( SOCKET_ERROR == bind( sock, (SOCKADDR*)&addr_in, sizeof(addr_in) ) )
	{
		return NULL;
	}

	if ( SOCKET_ERROR == listen( sock, SOMAXCONN ) )
	{
		return NULL;
	}

	OvSocketSPtr ret = OvNew OvSocket;
	ret->m_socket = sock;
	return ret;
}

OvBool OvSocket::Startup()
{
	WSADATA wsa;
	return ( WSAStartup( MAKEWORD(2,2), &wsa ) == 0 );

}

OvBool OvSocket::Cleanup()
{
	return ( WSACleanup() == 0 );
}

OvBool OvSocket::GetPeerAddr( Address& addr )
{
	if ( m_socket != INVALID_SOCKET )
	{
		SOCKADDR_IN addr_in;
		int sz = sizeof( addr_in );
		getpeername( m_socket, (SOCKADDR*)&addr_in, &sz );
		addr.ip = inet_ntoa( addr_in.sin_addr );
		addr.port = ntohs( addr_in.sin_port );
		return true;
	}
	return false;
}

OvBool OvSocket::GetSockAddr( Address& addr )
{
	if ( m_socket != INVALID_SOCKET )
	{
		SOCKADDR_IN addr_in;
		int sz = sizeof( addr_in );
		getsockname( m_socket, (SOCKADDR*)&addr_in, &sz );
		addr.ip = inet_ntoa( addr_in.sin_addr );
		addr.port = ntohs( addr_in.sin_port );
		return true;
	}
	return false;
}