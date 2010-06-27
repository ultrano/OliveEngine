#pragma once
#include "OvResource.h"
#include "OvRenderingCommon.h"

class OvMesh : public OvResource
{
	OvRTTI_DECL(OvMesh);
	friend class OvMeshBuilder;
private:

	OvMesh( const SStreamInfo&	streamInfo );
public:
	~OvMesh(){};

	virtual	bool Load( const std::string& fileLocation ) override{return false;};
	void	Rendering();

public:

private:
	SStreamInfo	m_streamInfo;

};