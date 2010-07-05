#include "OvModel.h"
#include "OvMesh.h"
#include "OvMaterialManager.h"

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
	OvShaderManager::GetInstance()->SetVSConst( OvMatVSConst::Float4x3_World, GetWorldMatrix() );
	OvMatrix view_proj;
	OvShaderManager::GetInstance()->GetVSConst( OvMatVSConst::Matrix_ViewProject, view_proj );
	OvShaderManager::GetInstance()->SetVSConst( OvMatVSConst::Matrix_WorldViewProject, GetWorldMatrix() * view_proj );

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