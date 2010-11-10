#pragma once
#include "OvMeshLoaderBase.h"
#include "OvAutoPtr.h"
#include <string>

// �޽� ������ 3�ܰ�� ������Ű��
// �����غ��� ������ �ʴ´�.
class OvFileMeshLoader : public OvMeshLoaderBase
{
	OvRTTI_DECL(OvFileMeshLoader);
public:
	OvFileMeshLoader();
	~OvFileMeshLoader();
	virtual OvResourceSPtr Load( OvDataStream& stream ) override;
private:
	
	const char*	_readLine();

	SVertexStreamInfo _parseStreamLow();
	SVertexStreamInfo _parseStreamMedium();
	LPDIRECT3DINDEXBUFFER9	_parseIndexStream();

private:
	enum {MAX_READ_BUFFER_SIZE = 256};
	FILE* m_file;
	std::string m_readBuffer;
	OvDataStream* m_data;
};