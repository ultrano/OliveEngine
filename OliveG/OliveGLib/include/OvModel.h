#pragma once
#include "OvXObject.h"

class OvModel : public OvXObject
{
	OvRTTI_DECL(OvModel);
	OvPROPERTY_BAG_DECL(OvModel);
public:

	void	Render();

private:

	/*
	mesh_resource	m_meshResource;
	testure_resource m_textureResource;
	material_resource m_materialResource;
	*/

};