#pragma once
#include "OvXObject.h"

OvREF_POINTER(OvMesh);
OvREF_POINTER(OvTexture);

OvREF_POINTER(OvModel);
class OvModel : public OvXObject
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

	void	SetMesh(OvMeshSPtr);
	OvMeshSPtr GetMesh();

	void	SetStageTexture( TextureStage stageIndex, OvTextureSPtr texture );
	OvTextureSPtr GetStageTexture( TextureStage stageIndex);

	void	Render();

private:

	OvMeshSPtr		m_resourceMesh;
	OvTextureSPtr	m_stageTexture[ TextureStage::MaxStage ];
	/*
	mesh_resource	m_meshResource;
	testure_resource m_textureResource;
	material_resource m_materialResource;
	*/

};