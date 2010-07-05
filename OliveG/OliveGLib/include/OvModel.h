#pragma once
#include "OvXObject.h"

OvREF_POINTER(OvMesh);

OvREF_POINTER(OvModel);
class OvModel : public OvXObject
{
	OvRTTI_DECL(OvModel);
	OvPROPERTY_BAG_DECL(OvModel);
public:

	void	SetMesh(OvMeshSPtr);
	OvMeshSPtr GetMesh();

	void	Render();

private:

	OvMeshSPtr		m_resourceMesh;
	/*
	mesh_resource	m_meshResource;
	testure_resource m_textureResource;
	material_resource m_materialResource;
	*/

};