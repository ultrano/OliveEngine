#pragma once
#include "OvRefBase.h"
#include "OvAutoPtr.h"
#include "OvRenderingCommon.h"

//OvREF_POINTER(OvMesh);

class OvMeshBuilder : public OvMemObject
{
public:
	
	OvMeshBuilder(LPDIRECT3DDEVICE9 device):m_device(device){};
	
	OvBool	LoadMesh(/*��� ���*/);

private:

	LPDIRECT3DDEVICE9 m_device;

	//vertex_stream_table	m_vertexStreamTable;

};