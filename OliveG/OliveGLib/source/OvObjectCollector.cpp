#include "OvObjectCollector.h"
#include "OvObject.h"
#include "OvXNode.h"
#include <algorithm>

OvObjectCollector::OvObjectCollector()
{

}
OvObjectCollector::OvObjectCollector(OvObjectCollector& crCopy)
{
	m_tdObjArray = crCopy.m_tdObjArray;
}
OvObjectCollector::OvObjectCollector(const OvObjectCollector& crCopy)
{
	m_tdObjArray = crCopy.m_tdObjArray;
}
OvObjectCollector::~OvObjectCollector()
{
	Clear();
}
OvObjectSPtr	OvObjectCollector::GetByAt(int iIndex)
{
	return m_tdObjArray[iIndex];
}

struct SKObjectFindFunctorByName
{
	SKObjectFindFunctorByName(const string& strName):m_strName(strName),m_pObj(NULL){};
	void operator()(OvObjectSPtr pObj)
	{
		if(pObj && m_strName == string(pObj->GetName()) ) m_pObj=pObj;
	}
	const string	m_strName;
	OvObjectSPtr	m_pObj;
};
OvObjectSPtr	OvObjectCollector::GetByName(const char* pName)
{
	SKObjectFindFunctorByName	kFindFunctor(pName);
	std::for_each(m_tdObjArray.begin(),m_tdObjArray.end(),kFindFunctor);
	return kFindFunctor.m_pObj;
}

struct SKObjectFindFunctorByHandle
{
	SKObjectFindFunctorByHandle(OvObjectID& dhHandle):m_dhHandle(dhHandle),m_pObj(NULL){};
	void operator()(OvObjectSPtr pObj)
	{
		if(pObj && pObj->GetObjectID() == m_dhHandle ) m_pObj=pObj;
	}
	OvObjectID		m_dhHandle;
	OvObjectSPtr	m_pObj;
};
OvObjectSPtr	OvObjectCollector::GetByHandle(OvObjectID& dhHandle)
{
	SKObjectFindFunctorByHandle	kFindFunctor(dhHandle);
	std::for_each(m_tdObjArray.begin(),m_tdObjArray.end(),kFindFunctor);
	return kFindFunctor.m_pObj;
}

DWORD			OvObjectCollector::Count()
{
	return m_tdObjArray.size();
}
void			OvObjectCollector::Clear()
{
	m_tdObjArray.clear();
}
bool			OvObjectCollector::AddObject(OvObjectSPtr pObj)
{
	m_tdObjArray.push_back(pObj);
	return true;
}

bool			OvObjectCollector::AddObject(OvObjectCollector& pObjContainer)
{
	for (int i=0;i<pObjContainer.Count();++i)
	{
		AddObject(pObjContainer.GetByAt(i));
	}
	return pObjContainer.Count();
}

OvObjectSPtr	OvObjectCollector::RemoveObject(OvObjectSPtr pObj)
{
	if (pObj)
	{
		tdObjectArray::iterator	kIter = OvSTL_Find(m_tdObjArray,pObj);
		if (kIter != m_tdObjArray.end())
		{
			m_tdObjArray.erase(kIter);
			return pObj;
		}
	}
	return NULL;
}

bool			OvObjectCollector::IsCollected(OvObjectSPtr pObj)
{
	if (pObj)
	{
		for (int i=0;i<Count();++i)
		{
			OvObjectSPtr kpTarget = GetByAt(i);
			if (kpTarget == pObj)
			{
				return true;
			}
		}
	}
	return false;
}