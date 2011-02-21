
#include "include_header.h"
#include "OliveDevice.h"
#include "OvBuffer.h"
#include "OvBufferInputStream.h"
#include "OvBufferOutputStream.h"

GL_TEST_CASE_FUNC( buffer_test )
{
	OliveDevice::EngineOn();
	{
		OU::string::format("%d%d",1,2);
		OvBufferSPtr buf = OvBuffer::CreateBuffer( 1 );
		OvBufferInputStream bis( buf );
		OvBufferOutputStream bos( buf );

		OvString write_str = "Å×½ºÆ®ÀÌ±á";
		bos.Write( write_str );

		OvString read_str;
		bis.Read( read_str );

	}
	OliveDevice::EngineOff();
}