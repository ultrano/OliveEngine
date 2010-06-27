#include "OvMesh.h"
#include "OvRenderer.h"
OvRTTI_IMPL(OvMesh)

OvMesh::OvMesh( const SStreamInfo&	streamInfo )
	   : m_streamInfo( streamInfo )
{

};
void	OvMesh::Rendering()
{
	LPDIRECT3DDEVICE9 device = (LPDIRECT3DDEVICE9)OvRenderer::GetInstance()->GetDevice();
	if (device)
	{
		for each( stream_source_table::value_type tablePair in m_streamInfo.vertStreamTable )
		{
			size_t streamIndex = tablePair.first;
			SVertexStreamInfo vertexStream = tablePair.second;
			device->SetStreamSource( streamIndex, vertexStream.vertStream, 0, vertexStream.vertStride );
		}
		device->SetIndices( m_streamInfo.faceStream );
		device->SetVertexDeclaration( m_streamInfo.vertDecl );
		device->DrawIndexedPrimitive
			( D3DPT_TRIANGLELIST
			, 0
			, 0
			, m_streamInfo.vertexCount
			, 0
			, m_streamInfo.faceCount);
	}

}