#pragma once
#include "OvXNode.h"
#include "OvMesh.h"
#include "OvMaterial.h"

OvREF_POINTER(OvModel);
class OvModel : public OvXNode
{
	OvRTTI_DECL(OvModel);
	OvPROPERTY_BAG_DECL(OvModel);
public:

	// ���� ���׸��� �κ����� ����
	enum TextureStage
	{
		Diffuse,
		Normal,
		MaxStage
	};

	OvModel();
	~OvModel();

	void	SetMesh(OvMeshSPtr);
	OvMeshSPtr GetMesh();

	void	SetMaterial( OvMaterialSPtr	material );
	OvMaterialSPtr	GetMaterial();

	void	RenderWithoutMaterial();
	void	Render();

private:

	OvResourceTicketSPtr	m_material;
	OvMeshSPtr				m_resourceMesh;

};