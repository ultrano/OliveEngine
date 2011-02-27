
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
		OvBufferSPtr buf = OvBuffer::CreateBuffer( 1 );
		OvOutputStreamSPtr ops;
		OvInputStreamSPtr ips;

		//! Buffer Stream
		OvString write_str = "Å×½ºÆ®ÀÌ±á";
		OvUInt	wuint = 111;
		OvFloat	wfloat = 1234.12423;
		ops = OvNew OvBufferOutputStream( buf );
		ops->Write( wuint );
		ops->Write( write_str );
		ops->Write( wfloat );
		ops = NULL;

		OvString read_str;
		OvUInt	ruint = 0;
		OvFloat	rfloat = 0;
		ips = OvNew OvBufferInputStream( buf );
		ips->Read( ruint );
		ips->Read( read_str );
		ips->Read( rfloat );
		ips = NULL;

	}
	OliveDevice::EngineOff();
}

GL_TEST_CASE_FUNC( file_buffer_test )
{
	OliveDevice::EngineOn();
	{
		OvString write_str = "Å×½ºÆ®ÀÌ±á";
		OvString read_str;

		OvOutputStreamSPtr ops;
		OvInputStreamSPtr ips;

		ops = OvNew OvFileOutputStream( "./test.txt" );
		ops->Write( write_str );
		ops = NULL;

		ips = OvNew OvFileInputStream( "./test.txt" );
		ips->Read( read_str );
		ips = NULL;
	}
	OliveDevice::EngineOff();
}