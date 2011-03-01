#include "include_header.h"
#include "OvFile.h"
#include "OvBuffer.h"
#include "OvPoint3.h"
#include "OvUtility.h"

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
		fos.Write( OU::d3dx9::VertexElementTypeSize("float3") ); // element size
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
		fos.Write( OU::d3dx9::VertexElementTypeSize("float2") ); // element size
		fos.Write(3); // element count
		fos.Write( OvPoint2(0,0) );
		fos.Write( OvPoint2(0,1) );
		fos.Write( OvPoint2(1,0) );
		fos.Write("</element>");

		fos.Write("</vertices>");

		fos.Write("<indices>");
		fos.Write(1); // element count
		//std::tr1::array<OvUInt,3>(0,0,0);
		//fos.Write( OvUInt(0,0,0)[3] );
		fos.Write("</indices>");

		fos.Close();

		OvFileInputStream fis("./vertex.vdata");
		OvUInt stream; fis.Read( stream );
		OvString type; fis.Read( type );
		OvString method; fis.Read( method );
		OvString usage; fis.Read( usage );
		OvUInt usageindex; fis.Read( usageindex );
		OvUInt esize; fis.Read( esize );
		OvUInt count; fis.Read( count );

		OvArrayAutoPtr<OvByte> element = new OvByte[esize];
		OvBufferSPtr buf = OvBuffer::CreateBuffer( esize * count );
		OvBufferOutputStream bos( buf );
		while ( count-- )
		{
			fis.ReadBytes( element.GetRear(), esize );
			bos.WriteBytes( element.GetRear(), esize );
		}

		OvBufferInputStream bis(buf);
		OvPoint3 pt0; bis.Read(pt0);
		OvPoint3 pt1; bis.Read(pt1);
		OvPoint3 pt2; bis.Read(pt2);
		fis.Close();

	}
	OliveDevice::EngineOff();
}