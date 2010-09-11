#include "OvModel.h"
#include "OvMaterialManager.h"
#include "OvRegisterableProperties.h"
#include "OvFileMeshLoader.h"
#include "OvTextureLoader.h"

OvRTTI_IMPL(OvModel)
OvPROPERTY_BAG_BEGIN(OvModel)
	OvPROPERTY_BAG_REGISTER( OvPropAccesser_resource, m_material )
	OvPROPERTY_BAG_REGISTER( OvPropAccesser_resource, m_resourceMesh )
OvPROPERTY_BAG_END(OvModel)

OvModel::OvModel()
{

}

OvModel::~OvModel()
{

}
void OvModel::SetMesh( OvMeshSPtr resource )
{
	m_resourceMesh = resource;
}

OvMeshSPtr OvModel::GetMesh()
{
	return m_resourceMesh;
}

void OvModel::SetMaterial( OvMaterialSPtr material )
{
	m_material = material;
}

OvMaterialSPtr OvModel::GetMaterial()
{
	return m_material;
}

void	OvModel::Render()
{
	if ( m_material )
	{
		m_material->ApplyMaterial();
	}
	OvShaderManager::GetInstance()->SetVSConst( OvMatVSConst::World, GetWorldMatrix() );
	OvMatrix view_proj;
	OvShaderManager::GetInstance()->GetVSConst( OvMatVSConst::ViewProject, view_proj );
	OvShaderManager::GetInstance()->SetVSConst( OvMatVSConst::WorldViewProject, GetWorldMatrix() * view_proj );

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