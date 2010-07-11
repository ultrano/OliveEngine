#include "OvMesh.h"
#include "OvRenderer.h"

OvRTTI_IMPL(OvMesh)


OvMesh::OvMesh()
{

}

OvMesh::~OvMesh()
{

}
void	OvMesh::Rendering( MeshDetail meshDetail )
{
	meshDetail = (meshDetail < Low)? Low : meshDetail;
	meshDetail = (meshDetail > High)? High : meshDetail;

	for( int i = 0 
		; i <= OvMesh::High
		; ++i)
	{
		OvRenderer::GetInstance()->SetVertexStream( i, NULL );
	}

	for( int i = 0 
		; i <= meshDetail
		; ++i)
	{
		OvRenderer::GetInstance()->SetVertexStream( i, &(m_renderData->vertStreamInfo[ i ]) );
	}

	OvRenderer::GetInstance()->SetIndexStream( m_renderData->faceStream );

	OvRenderer::GetInstance()->SetVertexDeclaration( m_renderData->vertDecl );

	bool result = OvRenderer::GetInstance()->DrawPrimitive( D3DPRIMITIVETYPE::D3DPT_TRIANGLELIST, m_renderData->faceCount );

}