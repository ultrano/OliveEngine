#include "OvObjectCollector.h"
#include "OvObject.h"
#include "OvObjectID.h"
#include <algorithm>
using namespace std;

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
OvObjectSPtr	OvObjectCollector::GetByName( const OvString& name )
{
	for each( tdObjectArray::value_type obj in m_tdObjArray )
	{
		if ( obj->GetName() == name )
		{
			return obj;
		}
	}
	return NULL;
}
OvObjectSPtr	OvObjectCollector::GetByID( const OvObjectID& objectID )
{
	for each( tdObjectArray::value_type obj in m_tdObjArray )
	{
		if ( obj->GetObjectID() == objectID )
		{
			return obj;
		}
	}
	return NULL;
}

DWORD			OvObjectCollector::Count()
{
	return (DWORD)m_tdObjArray.size();
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
	m_tdObjArray.reserve( pObjContainer.Count() );
	for ( unsigned  i = 0 ; i < (unsigned)pObjContainer.Count() ; ++i )
	{
		m_tdObjArray.push_back( pObjContainer.GetByAt(i) );
	}
	return ( m_tdObjArray.size() != 0 );
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

OvObjectSPtr OvObjectCollector::RemoveObject( const OvObjectID& objectID )
{
	OvObjectSPtr object = GetByID( objectID );
	if ( object )
	{
		return RemoveObject( object );
	}
	return NULL;
}
bool			OvObjectCollector::IsCollected(OvObjectSPtr pObj)
{
	if (pObj)
	{
		for ( unsigned i = 0 ; i < (unsigned)Count() ; ++i )
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