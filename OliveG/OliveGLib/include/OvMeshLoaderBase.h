#pragma once
#include "OvMesh.h"

class OvMeshLoaderBase : public OvResourceLoader
{
protected:
	void	SetRenderData(OvMeshSPtr mesh, OvMesh::SRenderData* renderData);
	OvMeshSPtr	_buildMesh
		( SVertexStreamInfo& streamLow
		, SVertexStreamInfo& streamMedium
		, SVertexStreamInfo& streamHigh
		, LPDIRECT3DVERTEXDECLARATION9 declVert
		, size_t countVert
		, LPDIRECT3DINDEXBUFFER9 streamFace
		, size_t countFace );
};