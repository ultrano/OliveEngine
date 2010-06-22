#include "OvRenderableObject.h"
#include "OvMaterial.h"
#include "OvAutoPtr.h"
#include "OvRenderer.h"


OvRTTI_IMPL(OvRenderableObject,OvXObject);

struct OvRenderableObject::OvPimple : OvMemObject
{
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
}
