#pragma once
#include "OvResource.h"
#include "OvAutoPtr.h"
#include "OvRenderingCommon.h"

OvREF_POINTER(OvMesh)
class OvMesh : public OvResource
{
	OvRTTI_DECL(OvMesh);
	friend class OvMeshLoaderBase;
public:
	enum MeshDetail
	{
		Low,
		Medium,
		High,
		MaxLevel,
	};
	struct SRenderData
	{
		SRenderData():faceStream(NULL), vertDecl(NULL), vertexCount(0), faceCount(0){};
		SVertexStreamInfo	vertStreamInfo[ MaxLevel ];
		LPDIRECT3DVERTEXDECLARATION9 vertDecl;
		size_t	vertexCount;
		LPDIRECT3DINDEXBUFFER9	faceStream;
		size_t	faceCount;
	};

	OvMesh();
	~OvMesh();

	void	Rendering( MeshDetail meshDetail = High );

private:

	OvAutoPtr<SRenderData>	m_renderData;

};