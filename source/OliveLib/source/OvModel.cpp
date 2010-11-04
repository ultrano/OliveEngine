#include "OvModel.h"
#include "OvRegisterableProperties.h"
#include "OvFileMeshLoader.h"
#include "OvTextureLoader.h"
#include "OvResourceManager.h"
#include "OvShaderManager.h"

OvRTTI_IMPL(OvModel)
OvPROPERTY_BAG_BEGIN(OvModel)
	OvPROPERTY_BAG_REGISTER( OvPropAccesser_resource_ticket, m_material )
	OvPROPERTY_BAG_REGISTER( OvPropAccesser_resource_ticket, m_mesh )
OvPROPERTY_BAG_END(OvModel)

OvModel::OvModel()
: m_material( NULL )
, m_mesh( NULL )
{

}

OvModel::~OvModel()
{

}
void OvModel::SetMesh( OvMeshSPtr resource )
{
	m_mesh = OvResourceManager::GetInstance()->FindTicket( resource );
}

OvMeshSPtr OvModel::GetMesh()
{
	return m_mesh->CheckOut();
}

void OvModel::SetMaterial( OvMaterialSPtr material )
{
	m_material = OvResourceManager::GetInstance()->FindTicket( material );
}

OvMaterialSPtr OvModel::GetMaterial()
{
	return m_material->CheckOut();
}


void OvModel::RenderWithoutMaterial()
{
	if ( false == GetControlFlag( VISIBLE ) )
	{
		return ;
	}

	OvShaderManager::GetInstance()->SetVSConst( OvVShaderConst::World, GetWorldMatrix() );

	OvMatrix temp_mat;
	
	OvShaderManager::GetInstance()->GetVSConst( OvVShaderConst::ViewProject, temp_mat );
	OvShaderManager::GetInstance()->SetVSConst( OvVShaderConst::WorldViewProject, GetWorldMatrix() * temp_mat );

	if ( GetMesh() )
	{
		GetMesh()->Rendering();
	}
}

void	OvModel::Render()
{
	if ( false == GetControlFlag( VISIBLE ) )
	{
		return ;
	}
	if ( OvMaterialSPtr	material = GetMaterial() )
	{
		material->ApplyMaterial();
	}
	OvShaderManager::GetInstance()->SetVSConst( OvVShaderConst::World, GetWorldMatrix() );
	OvMatrix view_proj;
	OvShaderManager::GetInstance()->GetVSConst( OvVShaderConst::ViewProject, view_proj );
	OvShaderManager::GetInstance()->SetVSConst( OvVShaderConst::WorldViewProject, GetWorldMatrix() * view_proj );

	if ( GetMesh() )
	{
		GetMesh()->Rendering();
	}
}
