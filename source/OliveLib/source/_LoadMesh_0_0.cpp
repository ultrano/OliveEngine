#include "OvMeshLoad.h"
#include "OvMesh.h"
#include "OvBuffer.h"
#include "OvUtility_d3dx9.h"
#include "OvRenderer.h"
#include <d3dx9.h>

class OvMesh_0_0 : public OvMesh
{
	
	struct streamdata
	{
		OvUInt index;
		LPDIRECT3DVERTEXBUFFER9 buffer;
		OvUInt stride;
	};
	struct elementdata
	{
		OvUInt		 targetstream;
		OvBufferSPtr buffer;
		OvUInt		 count;
		OvUInt		 offset;
		OvSize		 size;
	};

private:

	//! render members

	OvVector< streamdata > m_vstream;
	OvUInt	m_vertex_count;
	LPDIRECT3DVERTEXDECLARATION9 m_vdecl;

	LPDIRECT3DINDEXBUFFER9	m_ibuffer;
	OvUInt	m_index_count;
	D3DPRIMITIVETYPE m_primitive;

	//

	virtual void Draw()
	{
		HRESULT hr = E_FAIL;
		OvDevice device = OvRenderer::GetInstance()->GetDevice();
		for each ( const streamdata& val in m_vstream )
		{
			hr = device->SetStreamSource( val.index, val.buffer, 0, val.stride );
		}
		hr = device->SetVertexDeclaration( m_vdecl );
		hr = device->SetIndices( m_ibuffer );
		hr = device->DrawPrimitive( m_primitive, 0, m_index_count );
	}
private:

	//! load members
	OvString m_tag;
	OvMap<OvUInt,OvUInt>		m_streamsize;
	OvMap<OvUInt,OvUInt>		m_streamstride;
	OvVector<D3DVERTEXELEMENT9> m_dxverelems;
	//

public:

	void	load( OvInputStream& input )
	{
		if ( input.Read(m_tag) && "<vertices>" == m_tag )
		{
			loadvertices(input);
		}

		if ( input.Read(m_tag) && "<indices>" == m_tag )
		{
			OvString primtype;
			input.Read( primtype );
			m_primitive = OU::d3dx9::PrimitiveType( primtype );
			OvSize indexsize;	input.Read(indexsize);
			OvUInt indexcount;	input.Read(indexcount);
			OvSize bufsize = indexsize * indexcount;

			OvBufferSPtr buf = OvBuffer::CreateBuffer( bufsize );
			input.ReadBytes( buf->Pointer(), bufsize );

			OvDevice device = OvRenderer::GetInstance()->GetDevice();
			m_ibuffer = OU::d3dx9::CreateIndexBuffer( device, buf );
			m_index_count = indexcount;
		}
	}

private:
	void	loadvertices( OvInputStream& input )
	{
		OvMap<OvUInt,OvBufferSPtr>	streambuffers;

		OvVector<elementdata>		elements;

		while ( input.Read(m_tag) && ("<element>" == m_tag) )
		{
			elementdata elem;
			
			loadelement( input, elem );
			
			elements.push_back( elem );

			if ( input.Read(m_tag) && "</element>" == m_tag ) continue;
		}

		OvDevice device = OvRenderer::GetInstance()->GetDevice();
		m_vdecl = OU::d3dx9::CreateVertexDeclaration( device, &m_dxverelems[0] );
		for each ( const OvMap<OvUInt,OvUInt>::value_type& val in m_streamsize )
		{
			OvUInt stream_index = val.first;
			OvSize bufsize = val.second;

			OvBufferSPtr streambuf = OvBuffer::CreateBuffer( bufsize );
			streambuffers[stream_index] = streambuf;

			OvSize stride = m_streamstride[stream_index];
			for ( OvUInt i = 0 ; i < elements.size() ; ++i )
			{
				elementdata& elem = elements[i];
				OvBufferOutputStream bos( streambuf );

				bos.Skip( elem.offset );
				for ( OvUInt count = 0 ; count < elem.count ; ++count )
				{
					bos.WriteBytes( elem.buffer->Pointer() + (count*elem.size), elem.size );
					bos.Skip( stride - elem.size );
				}
			}
			OvMesh_0_0::streamdata sdata;
			sdata.index = stream_index;
			sdata.buffer = OU::d3dx9::CreateVertexBuffer( device, streambuf );
			sdata.stride = stride;
			m_vstream.push_back( sdata );
		}
		
	}

	void loadelement( OvInputStream &input, elementdata &elem ) 
	{
		OvUInt stream;			input.Read( stream );
		OvString type;			input.Read( type );
		OvString method;		input.Read( method );
		OvString usage;			input.Read( usage );
		OvUInt usageindex;		input.Read( usageindex );
		OvUInt count;			input.Read( count );
		OvUInt esize =			OU::d3dx9::VertexElementTypeSize( type );

		D3DVERTEXELEMENT9 decl = OU::d3dx9::VertexElement( stream
			, m_streamstride[stream]
		, type
			, method
			, usage
			, usageindex );

		m_dxverelems.push_back( decl );
		elem.count = count;
		elem.targetstream = stream;
		elem.offset = m_streamstride[stream];
		elem.size = esize;

		m_streamstride[stream] += esize;

		OvSize bufsize = esize * count;
		m_streamsize[stream] += bufsize;

		OvBufferSPtr buf = OvBuffer::CreateBuffer( bufsize );
		input.ReadBytes( buf->Pointer(), bufsize );

		elem.buffer = buf;
	}

};

OvMeshSPtr LoadMesh_0_0( OvInputStream& input )
{
	OvMesh_0_0* mesh = OvNew OvMesh_0_0;
	mesh->load( input );
	return mesh;
}
