#pragma once
#include "OvResource.h"
#include "OvAutoPtr.h"

struct SRenderData;
OvREF_POINTER(OvMesh)
class OvMesh : public OvResource
{
	OvRTTI_DECL(OvMesh);

public:

	enum RenderLevel
	{
		Pos_Norm,
		MaxLevel,
	};

	OvMesh();
	~OvMesh();

	virtual bool Load( const std::string& fileLocation ) override;

	void	Rendering();

private:

	// mesh_render_level

	OvAutoPtr<SRenderData>	m_renderData;

};