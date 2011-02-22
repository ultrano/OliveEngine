
#include "include_header.h"
#include "OliveDevice.h"
#include "OvBuffer.h"
#include "OvBufferInputStream.h"
#include "OvBufferOutputStream.h"
#include "OvFileInputStream.h"
#include "OvFileOutputStream.h"

GL_TEST_CASE_FUNC( buffer_test )
{
	OliveDevice::EngineOn();
	{
		OU::string::format("%d%d",1,2);
		OvBufferSPtr buf = OvBuffer::CreateBuffer( 1 );
		OvOutputStreamSPtr ops;
		OvInputStreamSPtr ips;
		OvString write_str = "Å×½ºÆ®ÀÌ±á";
		OvString read_str;

		//! Buffer Stream
// 		ops = OvNew OvBufferOutputStream( buf );
// 		ips = OvNew OvBufferInputStream( buf );

		//! File Stream
		ops = OvNew OvFileOutputStream( "./test.txt" );
		ops->Write( write_str );
		ops = NULL;

		ips = OvNew OvFileInputStream( "./test.txt" );
		ips->Read( read_str );
		ips = NULL;

	}
	OliveDevice::EngineOff();
}