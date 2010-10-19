#include "OvSceneBuilder.h"
#include "tinyxml.h"
#include "OvMesh.h"
#include "OvXNode.h"
#include "OvRenderer.h"
#include <map>


struct SNodeInfo
{
	OvXNodeSPtr			mNode;
	string				mNodeType;
	int					mLinkMeshHandle;
	int					mParentHandle;
};

struct OvSceneBuilder::OvPimple : OvMemObject
{
	//map<int,OvMeshObjectSPtr>		mMeshTable;
	map<int,SNodeInfo>				mNodeTable;
	DWORD							mMaxVertexBufferSize;
	DWORD							mMaxIndexBufferSize;
};

OvSceneBuilder::OvSceneBuilder()
:m_pPimple(OvNew OvSceneBuilder::OvPimple)
{

}
OvSceneBuilder::~OvSceneBuilder()
{

}

OvXNodeSPtr	OvSceneBuilder::BuildScene(const char* pExportInfoFile)
{
	return NULL;
}
void	OvSceneBuilder::BuildMeshObject(const char* pFile)
{

}
void	OvSceneBuilder::BuildMesh(const char* pFile)
{

}

