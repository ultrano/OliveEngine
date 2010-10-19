#include "OvObjectManager.h"
#include "OvStringUtility.h"
#include "OvObject.h"
#include <map>

OvObjectManager::OvObjectManager()
{
}
OvObjectManager::~OvObjectManager()
{
}

OvObjectID		OvObjectManager::AllocObjectID(OvObject* _pObject)
{
	m_maxID.core++;
	m_objectTable[ m_maxID ] = _pObject;

	return m_maxID;
}

void		OvObjectManager::RecallObjectID(OvObject* _pObject)
{
	//! ������Ʈ�� ������Ʈ ���̺��� �����Ѵ�.
	m_objectTable.erase(_pObject->GetObjectID());
}
OvObject*			OvObjectManager::FindObject(const OvObjectID& rObjHandle)
{
	if (m_objectTable.find(rObjHandle) != m_objectTable.end())
	{
		return m_objectTable[rObjHandle];
	}
	return NULL;
}