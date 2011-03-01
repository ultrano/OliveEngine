
#include "include_header.h"
#include "OliveDevice.h"
#include "OvFile.h"
#include "OvBuffer.h"
#include "OvObject.h"
#include "OvCamera.h"

GL_TEST_CASE_FUNC( object_file_streaming_test )
{
	OliveDevice::EngineOn();
	{
		{
			OvFileOutputStream fos( "./object.bin" );
			OvObjectOutputStream foos( &fos );

			OvXObjectSPtr xobj = OvNew OvXObject;
			OvCameraSPtr camera = OvNew OvCamera;
			OvXNodeSPtr xnode = OvNew OvXNode;
			xnode->AttachChild(xobj);
			xnode->AttachChild(camera);

			foos.Serialize( xnode );
		}
		{
			OvFileInputStream fis( "./object.bin" );
			OvObjectInputStream fois( &fis );

			OvObjectSPtr fobj = fois.Deserialize();
		}
	}
	OliveDevice::EngineOff();
}
GL_TEST_CASE_FUNC( object_buffer_streaming_test )
{
	OliveDevice::EngineOn();
	{
		OvBufferSPtr buf = OvBuffer::CreateBuffer( 128 );
		{
			OvBufferOutputStream bos( buf );
			OvObjectOutputStream boos( &bos );

			OvXObjectSPtr xobj = OvNew OvXObject;
			OvCameraSPtr camera = OvNew OvCamera;
			OvXNodeSPtr xnode = OvNew OvXNode;
			xnode->AttachChild(xobj);
			xnode->AttachChild(camera);

			boos.Serialize( xnode );
		}
		{
			OvBufferInputStream bis( buf );
			OvObjectInputStream bois( &bis );
			OvObjectSPtr bobj = bois.Deserialize();
		}
	}
	OliveDevice::EngineOff();
}

GL_TEST_CASE_FUNC( object_cloning_test )
{
	OliveDevice::EngineOn();
	{
		OvCameraSPtr camera = OvNew OvCamera;
		OvCameraSPtr clone_camera = camera->Clone();
	}
	OliveDevice::EngineOff();
}

GL_TEST_CASE_FUNC( olive_utility_test )
{
	OliveDevice::EngineOn();
	{
		OvString path = "C:\\Documents and Settings\\hahasasa\\My Documents\\Downloads\\UI_Prototype.pdf";
		OvString ret;
		ret = OU::path::GetBasePath( path );
		ret = OU::path::GetExtention( path );
		ret = OU::path::GetFileName( path );
		ret = OU::path::GetFileSpec( path );

		path = OU::string::replace( path, "hahasasa", "ultrano");

	}
	OliveDevice::EngineOff();
}