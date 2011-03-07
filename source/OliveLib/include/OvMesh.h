#pragma once
#include "OvResource.h"

OvREF_POINTER(OvMesh)
interface_class OvMesh : public OvResource
{
	OvRTTI_DECL(OvMesh);
public:
	OvMesh();
	~OvMesh();
	virtual void	Draw() = 0;

};