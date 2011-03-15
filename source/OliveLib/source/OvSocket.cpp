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
