#include "include_header.h"
#include "OliveDevice.h"
#include "OvFile.h"
#include "OvBuffer.h"
#include "OvPoint3.h"
#include "OvUtility.h"
#include "OvMeshLoad.h"

GL_TEST_CASE_FUNC( vertex_make_test )
{

	OliveDevice::EngineOn();
	{
		OvFileOutputStream fos("./vertex.vdata");
		fos.Write("<vertices>");

		fos.Write("<element>");
		fos.Write(0); // stream
		fos.Write("float3"); // type
		fos.Write("default"); // method
		fos.Write("position"); // usage
		fos.Write(0); // usageindex
		fos.Write(3); // element count
		fos.Write( OvPoint3(0,0,0) );
		fos.Write( OvPoint3(0,1,0) );
		fos.Write( OvPoint3(1,0,0) );
		fos.Write("</element>");

		fos.Write("<element>");
		fos.Write(0); // stream
		fos.Write("float2"); // type
		fos.Write("default"); // method
		fos.Write("texcoord"); // usage
		fos.Write(0); // usageindex
		fos.Write(3); // element count
		fos.Write( OvPoint2(0,0) );
		fos.Write( OvPoint2(0,1) );
		fos.Write( OvPoint2(1,0) );
		fos.Write("</element>");

		fos.Write("</vertices>");

		fos.Write("<indices>");
		fos.Write("trianglelist"); // primitive type
		fos.Write( sizeof(OvUShort)*3); // element size
		fos.Write(1); // element count
		OvUInt indices[]={0,1,2};
		fos.Write( indices );
		fos.Write("</indices>");

		fos.Close();

		OvDevice device = OvRenderer::GetInstance()->GetDevice();
		OvFileInputStream fis("./vertex.vdata");
		OvMeshSPtr mesh = LoadMesh_0_0( fis );
		device->BeginScene();
		mesh->Draw();;
		device->EndScene();
		fis.Close();

	}
	OliveDevice::EngineOff();
}