#include "include_header.h"
#include "OvSocket.h"

GL_TEST_CASE_FUNC( socket_test )
{
	WSADATA wsa;
	WSAStartup(MAKEWORD(2,2),&wsa);
	OliveDevice::EngineOn();
	{
		OvSocketSPtr socket = OvSocket::Connect("192.168.2.55",11011);
	}
	OliveDevice::EngineOff();
	WSACleanup();
}