#include "OvMeshLoaderBase.h"
#include "OvMesh.h"
#include "OvAutoPtr.h"

OvRTTI_IMPL(OvMeshLoaderBase);

void OvMeshLoaderBase::SetRenderData( OvMeshSPtr mesh, OvMesh::SRenderData* renderData )
{
	if ( mesh )
	{
		mesh->m_renderData = renderData;
	}
}

OvMeshSPtr OvMeshLoaderBase::_buildMesh( SVertexStreamInfo& streamLow
								 , SVertexStreamInfo& streamMedium
								 , SVertexStreamInfo& streamHigh
								 , LPDIRECT3DVERTEXDECLARATION9 declVert
								 , UINT countVert
								 , LPDIRECT3DINDEXBUFFER9 streamFace
								 , UINT countFace )
{
	OvAutoPtr< OvMesh::SRenderData > renderData = OvNew OvMesh::SRenderData;

	renderData->vertStreamInfo[ OvMesh::Geometry ] = streamLow;
	renderData->vertStreamInfo[ OvMesh::TextureCoord ] = streamMedium;
	renderData->vertStreamInfo[ OvMesh::Blend ] = streamHigh;
	renderData->vertDecl = declVert;
	renderData->vertexCount = countVert;
	renderData->faceStream = streamFace;
	renderData->faceCount = countFace;

	OvMeshSPtr mesh = OvNew OvMesh;
	mesh->m_renderData = renderData.Release();
	return mesh;
}