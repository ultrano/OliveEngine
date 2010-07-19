#pragma once
#include "OvMeshLoaderBase.h"

class OvFileMeshLoader : public OvMeshLoaderBase
{
	OvRTTI_DECL(OvFileMeshLoader);
public:
	virtual OvResourceSPtr Load( const std::string& fileLocation ) override;
private:
	
	const char*	_readLine();

	SVertexStreamInfo _parseStreamLow();
	SVertexStreamInfo _parseStreamMedium();
	LPDIRECT3DINDEXBUFFER9	_parseIndexStream();

private:
	enum {MAX_READ_BUFFER_SIZE = 256};
	FILE* m_file;
	char m_readBuffer[ MAX_READ_BUFFER_SIZE ];
};