#include "OvSocket.h"

//#include <winsock2.h>
OvRTTI_IMPL( OvSocket );

OvSocketSPtr OvSocket::Connect( const string& ip, OvUInt port )
{
	OvSocketSPtr ovsocket = OvNew OvSocket;
	SOCKET sock = socket( AF_INET, SOCK_STREAM, 0 );
	SOCKADDR_IN add_in;
	add_in.sin_family = AF_INET;
	add_in.sin_port = htons( port );
	add_in.sin_addr.s_addr = inet_addr( ip.c_str() );

	connect( sock, (SOCKADDR*)&add_in, sizeof(add_in) );

	ovsocket->m_socket = sock;
	return ovsocket;
}
