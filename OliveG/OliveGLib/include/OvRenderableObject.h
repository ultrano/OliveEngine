#pragma once
#include "OvXObject.h"

// Class Predeclare;
class OvRenderer;
OvREF_POINTER(OvMesh);
OvREF_POINTER(OvMaterial);
//

OvREF_POINTER(OvRenderableObject);
class OvRenderableObject : public OvXObject
{
	OvRTTI_DECL(OvRenderableObject);


public:

	OvRenderableObject();
	~OvRenderableObject();

	void			SetMaterial(OvMaterialSPtr pMaterial);
	OvMaterialSPtr	GetMaterial();

	void		SetMesh(OvMeshSPtr pMesh);
	OvMeshSPtr	GetMesh();

	void	Render();
	void	RenderMaterialNonappliedMesh();

private:

	struct OvPimple;
	OvAutoPtr<OvPimple> m_pPimple;

};