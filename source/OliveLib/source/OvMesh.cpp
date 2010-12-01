#include "OvMesh.h"
#include "OvRenderer.h"

OvRTTI_IMPL(OvMesh)


OvMesh::OvMesh()
{

}

OvMesh::~OvMesh()
{
	if ( m_renderData )
	{
		for( OvInt i = 0 
			; i < STAGE_MAX
			; ++i)
		{
			SVertexStreamInfo& streamInfo = m_renderData->vertStreamInfo[ i ];
			if ( streamInfo.vertexStream )
			{
				streamInfo.vertexStream->Release();
			}
		}
		if ( m_renderData->faceStream )
		{
			m_renderData->faceStream->Release();
		}
		if ( m_renderData->vertDecl )
		{
			m_renderData->vertDecl->Release();
		}

	}
}
void	OvMesh::Rendering( StreamStage meshDetail )
{
	meshDetail = (meshDetail < Geometry)? Geometry : meshDetail;
	meshDetail = (meshDetail > Blend)? Blend : meshDetail;

	for( OvInt i = 0 
		; i < STAGE_MAX
		; ++i)
	{
		OvRenderer::GetInstance()->SetVertexStream( i, (m_renderData->vertStreamInfo[ i ]) );
	}

	OvRenderer::GetInstance()->SetIndexStream( m_renderData->faceStream );

	OvRenderer::GetInstance()->SetVertexDeclaration( m_renderData->vertDecl );

	bool result = OvRenderer::GetInstance()->DrawPrimitive( D3DPT_TRIANGLELIST, m_renderData->faceCount );

}