#include "include_header.h"
#include "OvFile.h"
#include "OvBuffer.h"
#include "OvPoint3.h"
#include "OvUtility.h"

void	loadvelement( OvString& tag, OvInputStream& input )
{
	OvVector<D3DVERTEXELEMENT9> verdec;
	OvMap<OvUInt,OvBufferSPtr>	streambuffers;
	OvMap<OvUInt,OvUInt>		streamsize;
	OvMap<OvUInt,OvUInt>		streamstride;

	OvVector<OvBufferSPtr>		elembuffers;
	OvVector<OvUInt>			elemcount;
	OvVector<OvUInt>			elemstream;
	OvVector<OvUInt>			elemoffset;
	OvVector<OvUInt>			elemsizes;

	while ( input.Read(tag) && ("<element>" == tag) )
	{
		OvUInt stream;			input.Read( stream );
		OvString type;			input.Read( type );
		OvString method;		input.Read( method );
		OvString usage;			input.Read( usage );
		OvUInt usageindex;		input.Read( usageindex );
		OvUInt count;			input.Read( count );
		OvUInt esize =			OU::d3dx9::VertexElementTypeSize( type );

		D3DVERTEXELEMENT9 decl = OU::d3dx9::VertexElement( stream
								, streamstride[stream]
								, type
								, method
								, usage
								, usageindex );

		verdec.push_back( decl );
		elemcount.push_back( count );
		elemstream.push_back( stream );
		elemoffset.push_back( streamstride[stream] );
		elemsizes.push_back( esize );

		streamstride[stream] += esize;

		OvSize bufsize = esize * count;
		streamsize[stream] += bufsize;

		OvBufferSPtr buf = OvBuffer::CreateBuffer( bufsize );
		input.ReadBytes( buf->Pointer(), bufsize );
		elembuffers.push_back( buf );
	}

	for each ( const OvMap<OvUInt,OvUInt>::value_type& val in streamsize )
	{
		OvUInt stream_index = val.first;
		OvSize bufsize = val.second;

		OvBufferSPtr streambuf = OvBuffer::CreateBuffer( bufsize );
		streambuffers[stream_index] = streambuf;

		OvSize stride = streamstride[stream_index];
		for ( OvUInt index = 0 ; index < elembuffers.size() ; ++index )
		{
			OvBufferOutputStream bos( streambuf );
			OvSize		 offset = elemoffset[index];
			OvSize		 size = elemsizes[index];
			OvBufferSPtr elembuf = elembuffers[ index ];

			bos.Skip(offset);
			for ( OvUInt count = 0 ; count < elemcount[index] ; ++count )
			{
				bos.WriteBytes( elembuf->Pointer() + (count*size), size );
				bos.Skip( stride - size );
			}
		}
	}

}
void	loadgeom( OvInputStream& input )
{
	OvString tag;

	if ( input.Read(tag) && "<vertices>" == tag )
	{
	}

	if ( input.Read(tag) && "indices" == tag )
	{
	}
}

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
		fos.Write( sizeof(OvUShort)*3); // element size
		fos.Write(1); // element count
		OvUInt indices[]={0,1,2};
		fos.Write( indices );
		fos.Write("</indices>");

		fos.Close();

		OvFileInputStream fis("./vertex.vdata");
		fis.Close();

	}
	OliveDevice::EngineOff();
}