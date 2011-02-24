
#include "include_header.h"
#include "OliveDevice.h"
#include "OvFile.h"
#include "OvObject.h"
#include "OvCamera.h"

GL_TEST_CASE_FUNC( object_streaming_test )
{
	OliveDevice::EngineOn();
	{
		{
			OvFileOutputStream fos( "./object.bin" );
			OvObjectOutputStream oos( &fos );
			OvXObjectSPtr xobj = OvNew OvXObject;
			OvCameraSPtr camera = OvNew OvCamera;
			OvXNodeSPtr xnode = OvNew OvXNode;
			xnode->AttachChild(xobj);
			xnode->AttachChild(camera);
			oos.Serialize( xnode );
		}
		{
			OvFileInputStream fis( "./object.bin" );
			OvObjectInputStream ois( &fis );
			OvObjectSPtr obj = ois.Deserialize();
		}
	}
	OliveDevice::EngineOff();
}