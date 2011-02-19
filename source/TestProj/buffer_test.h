
#include "include_header.h"
#include "OliveDevice.h"
#include "OvBuffer.h"
#include "OvBufferInputStream.h"
#include "OvBufferOutputStream.h"

GL_TEST_CASE_FUNC( buffer_test )
{
	OliveDevice::EngineOn();
	{
		OvBufferSPtr buf = OvBuffer::CreateBuffer( 1 );
		OvBufferInputStream bis( buf );
		OvBufferOutputStream bos( buf );

		OvChar write[] = "Å×½ºÆ®ÀÌ±á";
		bos.WriteBytes( (OvByte*)write, sizeof( write ) );

		OvChar read[256] = {0,};
		bis.ReadBytes( (OvByte*)read, sizeof( read ) );

		//bis.
	}
	OliveDevice::EngineOff();
}