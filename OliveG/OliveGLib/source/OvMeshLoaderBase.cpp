#include "OvMeshLoaderBase.h"
#include "OvAutoPtr.h"
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
								 , size_t countVert
								 , LPDIRECT3DINDEXBUFFER9 streamFace
								 , size_t countFace )
{
	OvAutoPtr< OvMesh::SRenderData > renderData = new OvMesh::SRenderData;

	renderData->vertStreamInfo[ OvMesh::Low ] = streamLow;
	renderData->vertStreamInfo[ OvMesh::Medium ] = streamMedium;
	renderData->vertStreamInfo[ OvMesh::High ] = streamHigh;
	renderData->vertDecl = declVert;
	renderData->vertexCount = countVert;
	renderData->faceStream = streamFace;
	renderData->faceCount = countFace;

	OvMeshSPtr mesh = new OvMesh;
	mesh->m_renderData = renderData.Release();
	return mesh;
}