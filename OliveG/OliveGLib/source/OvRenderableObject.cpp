#include "OvRenderableObject.h"
#include "OvMaterial.h"
#include "OvMesh.h"
#include "OvAutoPtr.h"
#include "OvRenderer.h"


OvRTTI_IMPL(OvRenderableObject,OvXObject);

struct OvRenderableObject::OvPimple : OvMemObject
{
	OvMeshSPtr	m_pMesh;
	OvMaterialSPtr	m_pMaterial;
};

OvRenderableObject::OvRenderableObject()
:m_pPimple(OvNew OvPimple)
{

};

OvRenderableObject::~OvRenderableObject()
{

};
void		OvRenderableObject::SetMaterial(OvMaterialSPtr pMaterial)
{
	m_pPimple->m_pMaterial = pMaterial;
}
OvMaterialSPtr OvRenderableObject::GetMaterial()
{
	return m_pPimple->m_pMaterial;
}
void		OvRenderableObject::SetMesh(OvMeshSPtr pMesh)
{
	m_pPimple->m_pMesh = pMesh;
}
OvMeshSPtr	OvRenderableObject::GetMesh()
{
	return m_pPimple->m_pMesh;
}
void	OvRenderableObject::Render()
{
	OvMaterialSPtr pMaterial = GetMaterial();
	if (pMaterial)
	{
		pMaterial->ApplyMaterial(this);
		RenderMaterialNonappliedMesh();
	}
}
void	OvRenderableObject::RenderMaterialNonappliedMesh()
{
	if (GetMesh())
	{
		OvRenderer::GetInstance()->DrawMesh(GetMesh());
	}
}
