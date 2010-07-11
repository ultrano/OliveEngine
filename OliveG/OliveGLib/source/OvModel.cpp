#include "OvModel.h"
#include "OvMesh.h"
#include "OvMaterialManager.h"
#include "OvTexture.h"

OvRTTI_IMPL(OvModel)
OvPROPERTY_BAG_BEGIN(OvModel)
OvPROPERTY_BAG_END(OvModel)



void OvModel::SetMesh( OvMeshSPtr resource )
{
	m_resourceMesh = resource;
}

OvMeshSPtr OvModel::GetMesh()
{
	return m_resourceMesh;
}
void	OvModel::Render()
{
	OvShaderManager::GetInstance()->SetVSConst( OvMatVSConst::World, GetWorldMatrix() );
	OvMatrix view_proj;
	OvShaderManager::GetInstance()->GetVSConst( OvMatVSConst::ViewProject, view_proj );
	OvShaderManager::GetInstance()->SetVSConst( OvMatVSConst::WorldViewProject, GetWorldMatrix() * view_proj );

	for ( int i = 0 
		; i < TextureStage::MaxStage 
		; ++i )
	{
		OvShaderManager::GetInstance()->SetTexture( i , m_stageTexture[i] );
	}

	if ( m_resourceMesh )
	{
		m_resourceMesh->Rendering();
	}

	/*
	m_meshResource;
	m_textureResource;
	m_materialResource;

	m_materialResource->

	*/
}

void OvModel::SetStageTexture( TextureStage stageIndex, OvTextureSPtr texture )
{
	m_stageTexture[stageIndex] = texture;
}

OvTextureSPtr OvModel::GetStageTexture( TextureStage stageIndex )
{
	return m_stageTexture[stageIndex];
}