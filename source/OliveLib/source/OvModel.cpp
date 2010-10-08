#include "OvModel.h"
#include "OvMaterialManager.h"
#include "OvRegisterableProperties.h"
#include "OvFileMeshLoader.h"
#include "OvTextureLoader.h"
#include "OvResourceManager.h"
#include "OvObjectProperties.h"
#include "OvPropAccesserNode.h"

OvRTTI_IMPL(OvModel)
OvPROPERTY_BAG_BEGIN(OvModel)
	OvPROPERTY_BAG_REGISTER( OvPropAccesser_resource_ticket, m_material )
	OvPROPERTY_BAG_REGISTER( OvPropAccesser_resource, m_resourceMesh )
OvPROPERTY_BAG_END(OvModel)

OvModel::OvModel()
: m_material( NULL )
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
	m_material = OvResourceManager::GetInstance()->CheckIn( material );
}

OvMaterialSPtr OvModel::GetMaterial()
{
	return m_material->CheckOut();
}


void OvModel::RenderWithoutMaterial()
{
	OvShaderManager::GetInstance()->SetVSConst( OvVShaderConst::World, GetWorldMatrix() );

	OvMatrix temp_mat;
	
	OvShaderManager::GetInstance()->GetVSConst( OvVShaderConst::ViewProject, temp_mat );
	OvShaderManager::GetInstance()->SetVSConst( OvVShaderConst::WorldViewProject, GetWorldMatrix() * temp_mat );

	if ( m_resourceMesh )
	{
		m_resourceMesh->Rendering();
	}
}

void	OvModel::Render()
{
	if ( OvMaterialSPtr	material = GetMaterial() )
	{
		material->ApplyMaterial();
	}
	OvShaderManager::GetInstance()->SetVSConst( OvVShaderConst::World, GetWorldMatrix() );
	OvMatrix view_proj;
	OvShaderManager::GetInstance()->GetVSConst( OvVShaderConst::ViewProject, view_proj );
	OvShaderManager::GetInstance()->SetVSConst( OvVShaderConst::WorldViewProject, GetWorldMatrix() * view_proj );

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

OvObjectSPtr OvModel::Clone()
{

	OvObjectProperties store;
	for ( OvRTTI * rtti = const_cast<OvRTTI*>(QueryRTTI())
		; NULL != rtti
		; rtti = const_cast<OvRTTI*>(rtti->GetBaseRTTI()))
	{
		OvPropertyBag* prop_bag = rtti->PropertyBag();
		if (prop_bag)
		{
			OvPropAccesserNode* prop_node = NULL;
			for (prop_node = prop_bag->BeginAccessNode()
				;prop_node != NULL
				;prop_node = prop_node->GetNext())
			{
				OvPropertyAccesser* prop_acces = prop_node->GetProperty();
				if (prop_acces)
				{
					prop_acces->Extract( this, store );
				}
			}
		}		
	}

	OvModelSPtr clone = OvNew OvModel();
	for ( OvRTTI * rtti = const_cast<OvRTTI*>(QueryRTTI())
		; NULL != rtti
		; rtti = const_cast<OvRTTI*>(rtti->GetBaseRTTI()))
	{
		OvPropertyBag* prop_bag = rtti->PropertyBag();
		if (prop_bag)
		{
			OvPropAccesserNode* prop_node = NULL;
			for (prop_node = prop_bag->BeginAccessNode()
				;prop_node != NULL
				;prop_node = prop_node->GetNext())
			{
				OvPropertyAccesser* prop_acces = prop_node->GetProperty();
				if (prop_acces)
				{
					prop_acces->Inject( clone.GetRear(), store );
				}
			}
		}		
	}
	return clone;
}