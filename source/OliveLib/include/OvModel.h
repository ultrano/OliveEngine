#pragma once
#include "OvXNode.h"
#include "OvMesh.h"
#include "OvMaterial.h"
#include "OvResourceTicket.h"

OvREF_POINTER(OvModel);
class OvModel : public OvXNode
{
	OvRTTI_DECL(OvModel);
	OvPROPERTY_BAG_DECL(OvModel);
public:

	// 요고는 마테리얼 부분으로 빼자
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
	OvResourceTicketSPtr	m_mesh;

};