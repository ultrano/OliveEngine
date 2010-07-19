#include "OvObjectCollector.h"
#include "OvObject.h"
#include "OvObjectID.h"
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
OvObjectSPtr	OvObjectCollector::GetByName(const char* pName)
{
	for each( tdObjectArray::value_type obj in m_tdObjArray )
	{
		if ( obj->GetName() == pName )
		{
			return obj;
		}
	}
	return NULL;
}
OvObjectSPtr	OvObjectCollector::GetByID(OvObjectID& dhHandle)
{
	for each( tdObjectArray::value_type obj in m_tdObjArray )
	{
		if ( obj->GetObjectID() == dhHandle )
		{
			return obj;
		}
	}
	return NULL;
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