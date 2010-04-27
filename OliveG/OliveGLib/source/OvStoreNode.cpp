#include "OvStoreNode.h"
#include "OvStoreData.h"
#include <vector>

OvRTTI_IMPL(OvStoreNode,OvStoreObject);

struct OvStoreNode::OvPimple : OvMemObject
{
	vector<OvAutoPtr<OvStoreObject>>	m_vecChildren;
};

OvStoreNode::OvStoreNode()
:m_pPimple(OvNew OvStoreNode::OvPimple)
{

}
OvStoreNode::~OvStoreNode()
{
	m_pPimple->m_vecChildren.clear();
}
unsigned int	OvStoreNode::ChildCount()
{
	return m_pPimple->m_vecChildren.size();
}
void	OvStoreNode::InsertObject(OvStoreObject* pObject)
{
	if (pObject)
	{
		m_pPimple->m_vecChildren.push_back(pObject->MakeCopyInstance());
	}
}
OvStoreObject*	OvStoreNode::FindChild(const char* pName)
{
	OvStoreObject* kpChild = NULL;
	int kiCount = m_pPimple->m_vecChildren.size();
	for (int i = 0 ; i < kiCount ; ++i)
	{
		kpChild = m_pPimple->m_vecChildren.at(i).GetRear();
		if (kpChild && kpChild->GetName() == string(pName))
		{
			return kpChild;
		}
	}
	return NULL;
}
OvStoreObject*	OvStoreNode::FindDataChild(const char* pName)
{
	OvStoreObject* kpObj = FindChild(pName);
	if (OvRTTI_IsClassOf(OvStoreData,kpObj))
	{
		return kpObj;
	}
	return NULL;
}
OvStoreObject*	OvStoreNode::FindNodeChild(const char* pName)
{
	OvStoreObject* kpObj = FindChild(pName);
	if (OvRTTI_IsClassOf(OvStoreNode,kpObj))
	{
		return kpObj;
	}
	return NULL;
}
OvStoreObject*	OvStoreNode::ChildAt(unsigned int iIndex)
{
	int kiCount = m_pPimple->m_vecChildren.size();
	if (iIndex < kiCount && iIndex >= 0)
	{
		OvStoreObject* kpChild = NULL;
		kpChild = m_pPimple->m_vecChildren.at(iIndex).GetRear();
		return kpChild;
	}
	return NULL;
}
OvStoreObject*	OvStoreNode::MakeCopyInstance()
{
	OvStoreNode* kpCopy = OvNew OvStoreNode;
	if (CopyTo(kpCopy))
	{
		return kpCopy;
	}
	OvDelete kpCopy;
	return NULL;
}
bool			OvStoreNode::CopyTo(OvStoreObject* pObj)
{
	if (OvRTTI_IsClassOf(OvStoreNode,pObj))
	{
		OvStoreNode* kpNode = (OvStoreNode*)pObj;
		kpNode->m_pPimple->m_vecChildren.clear();
		kpNode->SetName(GetName());

		unsigned int kiOriginSize = m_pPimple->m_vecChildren.size();

		for (unsigned int i = 0 ; i < kiOriginSize ; ++i)
		{
			OvStoreObject* kpOrigin = ChildAt(i);
			kpNode->InsertObject(kpOrigin);
		}
		return true;
	}
	return false;
}