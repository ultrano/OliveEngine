#pragma once
#include "OvRefBase.h"
#include "OvAutoPtr.h"
#include "OvRenderingCommon.h"

//OvREF_POINTER(OvMesh);

class OvMeshBuilder : public OvMemObject
{
public:
	
	OvMeshBuilder(LPDIRECT3DDEVICE9 device):m_device(device){};
	
	bool	LoadMesh(/*블라 블라*/);

	bool BuildVertexStream0(explicit stream_0_element_buffer& buffer);
	
	LPDIRECT3DINDEXBUFFER9	CreateIndexStream(explicit face_element_buffer& buffer);

private:

	LPDIRECT3DDEVICE9 m_device;

	vertex_stream_table	m_vertexStreamTable;

};