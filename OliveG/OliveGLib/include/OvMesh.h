#pragma once
#include "OvResource.h"
#include "OvAutoPtr.h"
#include "OvRenderingCommon.h"
#include "OvBitFlags.h"

OvREF_POINTER(OvMesh)
class OvMesh : public OvResource
{
	OvRTTI_DECL(OvMesh);
	friend class OvMeshLoaderBase;
public:
	enum StreamStage
	{
		Geometry,
		TextureCoord,
		Blend,
		STAGE_MAX,
	};
	struct SRenderData : OvMemObject
	{
		SRenderData():faceStream(NULL), vertDecl(NULL), vertexCount(0), faceCount(0){};
		SVertexStreamInfo	vertStreamInfo[ STAGE_MAX ];
		LPDIRECT3DVERTEXDECLARATION9 vertDecl;
		size_t	vertexCount;
		LPDIRECT3DINDEXBUFFER9	faceStream;
		size_t	faceCount;
	};

	OvMesh();
	~OvMesh();

	void	Rendering( StreamStage meshDetail = Blend );

private:

	OvAutoPtr<SRenderData>	m_renderData;

};