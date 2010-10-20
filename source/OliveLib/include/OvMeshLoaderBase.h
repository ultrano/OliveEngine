#pragma once
#include "OvMesh.h"

class OvMeshLoaderBase : public OvResourceLoader
{
	OvRTTI_DECL(OvMeshLoaderBase);
protected:
	void	SetRenderData(OvMeshSPtr mesh, OvMesh::SRenderData* renderData);
	OvMeshSPtr	_buildMesh
		( SVertexStreamInfo& streamLow
		, SVertexStreamInfo& streamMedium
		, SVertexStreamInfo& streamHigh
		, LPDIRECT3DVERTEXDECLARATION9 declVert
		, UINT countVert
		, LPDIRECT3DINDEXBUFFER9 streamFace
		, UINT countFace );
};