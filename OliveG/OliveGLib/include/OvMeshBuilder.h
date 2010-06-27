#pragma once
#include "OvRefBase.h"
#include "OvAutoPtr.h"
#include "OvRenderingCommon.h"

OvREF_POINTER(OvMesh);

class OvMeshBuilder : public OvMemObject
{
public:

	OvMeshBuilder();
	~OvMeshBuilder();
	
	void	SetGeometryBuffer(const geometry_element_buffer& buffer);
	const geometry_element_buffer&	GetGeometryBuffer();

	void	SetFaceBuffer( const face_element_buffer& buffer );
	const face_element_buffer GetFaceBuffer();

	OvMeshSPtr	BuildMesh();

private:
	
	LPDIRECT3DVERTEXDECLARATION9 _build_vertex_declare( LPDIRECT3DDEVICE9 device );
	LPDIRECT3DVERTEXBUFFER9 _build_vertex_stream( LPDIRECT3DDEVICE9 directDevice, const SBufferInfo& info );
	LPDIRECT3DINDEXBUFFER9	_build_index_stream(  LPDIRECT3DDEVICE9 directDevice , face_element_buffer& faceBuffer );
	void	_push_element_declare( WORD stream, WORD elemSize, BYTE elemType, BYTE elemUsage, size_t elemCount, void* buffer);
private:
	
	stream_source_info_array	m_streamSourceArray;	
	usage_overlap_count_table	m_usageCountTable;

	// holding member
	geometry_element_buffer		m_geometryBuffer;
	face_element_buffer			m_faceBuffer;

	// return member
	stream_source_table			m_streamSourceTable;
	LPDIRECT3DINDEXBUFFER9		m_faceStreamSource;
	LPDIRECT3DVERTEXDECLARATION9 m_vertexDeclaration;

};