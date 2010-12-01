#pragma once
#include "OvRefBase.h"
#include "OvAutoPtr.h"
#include "OvRenderingCommon.h"

//OvREF_POINTER(OvMesh);

class OvMeshBuilder : public OvMemObject
{
public:
	
	OvMeshBuilder(LPDIRECT3DDEVICE9 device):m_device(device){};
	
	OvBool	LoadMesh(/*블라 블라*/);

private:

	LPDIRECT3DDEVICE9 m_device;

	//vertex_stream_table	m_vertexStreamTable;

};