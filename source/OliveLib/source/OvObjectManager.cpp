#include "OvObjectManager.h"
#include "OvUtility.h"
#include "OvObject.h"
#include "OvThreadSync.h"
#include <map>

OvObjectManager::OvObjectManager()
{
}
OvObjectManager::~OvObjectManager()
{
}

OvObjectID		OvObjectManager::AllocObjectID(OvObject* _pObject)
{
	OvThreadSyncer<OvObjectManager>::OvSectionLock lock;
	m_maxID.core++;
	m_objectTable[ m_maxID ] = _pObject;

	return m_maxID;
}

void		OvObjectManager::RecallObjectID(OvObject* _pObject)
{
	OvThreadSyncer<OvObjectManager>::OvSectionLock lock;
	//! 오브젝트는 오브젝트 테이블에서 삭제한다.
	m_objectTable.erase(_pObject->GetObjectID());
}
OvObject*			OvObjectManager::FindObject(const OvObjectID& rObjHandle)
{
	OvThreadSyncer<OvObjectManager>::OvSectionLock lock;
	if (m_objectTable.find(rObjHandle) != m_objectTable.end())
	{
		return m_objectTable[rObjHandle];
	}
	return NULL;
}