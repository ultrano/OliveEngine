//#include "OvNodeTreeBuilder.h"
//#include "OvXNode.h"
//#include "tinyxml.h"
//
//
//typedef map<int,SNodeInheritInfo> tdNodeTable;
//struct OvNodeTreeBuilder::OvPimple : OvMemObject
//{
//	tdNodeTable	mObjectTable;
//};
//
//OvNodeTreeBuilder::OvNodeTreeBuilder()
//:m_pPimple(OvNew OvNodeTreeBuilder::OvPimple)
//{
//
//}
//OvNodeTreeBuilder::~OvNodeTreeBuilder()
//{
//
//}
//void		OvNodeTreeBuilder::AddElementObject(SNodeInheritInfo& rNodeInfo)
//{
//	m_pPimple->mObjectTable[rNodeInfo.mHandle] = rNodeInfo;
//}
//void		OvNodeTreeBuilder::AddElementObject(int iHandle,int iParentHandle,OvXObjectSPtr pObject)
//{
//	m_pPimple->mObjectTable[iHandle] = SNodeInheritInfo(iHandle,iParentHandle,pObject);
//}
//OvXNodeSPtr	OvNodeTreeBuilder::Build()
//{
//	OvXNodeSPtr	kpRootNode = OvNew OvXNode;
//	tdNodeTable::iterator kIter = m_pPimple->mObjectTable.begin();
//	for (;kIter != m_pPimple->mObjectTable.end();++kIter)
//	{
//		SNodeInheritInfo& krNodeInfo = kIter->second;
//		OvXObjectSPtr kpChildNode = krNodeInfo.mObject;
//		OvXNodeSPtr	kpParentNode = NULL;
//		if (m_pPimple->mObjectTable.find(krNodeInfo.mParentHandle) != m_pPimple->mObjectTable.end())
//		{
//			kpParentNode = m_pPimple->mObjectTable[krNodeInfo.mParentHandle].mObject;
//		}
//		if (kpParentNode && kpParentNode->IsNode())
//		{
//			kpParentNode->AttachChild(kpChildNode);
//		}
//	}
//	kIter = m_pPimple->mObjectTable.begin();
//	for (;kIter != m_pPimple->mObjectTable.end();++kIter)
//	{
//		SNodeInheritInfo& krNodeInfo = kIter->second;
//		OvXObjectSPtr kpChildNode = krNodeInfo.mObject;
//		if (kpChildNode->GetParent() == NULL)
//		{
//			kpRootNode->AttachChild(kpChildNode);
//		}
//	}
//	return kpRootNode;
//}