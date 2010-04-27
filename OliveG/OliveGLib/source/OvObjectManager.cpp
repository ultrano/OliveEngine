#include "OvObjectManager.h"
#include <algorithm>
#include <vector>
#include <map>
#include <queue>

OvSingletonEx_IMPL(OvObjectManager);

typedef map<OvObjectID,OvObject*>			OvObjectTable;


struct OvObjectManager::OvPimple : OvMemObject
{
	OvObjectID		m_hMaxHandle;
	OvObjectTable		m_tblObjectTable;

};

void	OvObjectManager::Singleton_InitializeProcessing()
{
	m_pPimple = OvNew OvObjectManager::OvPimple;
}
void	OvObjectManager::Singleton_TerminateProcessing()
{

}

OvObjectID		OvObjectManager::AllocObjectID(OvObject* _pObject)
{
	++m_pPimple->m_hMaxHandle;
	m_pPimple->m_tblObjectTable[m_pPimple->m_hMaxHandle] = _pObject;
	return m_pPimple->m_hMaxHandle;
}

void		OvObjectManager::RecallObjectID(OvObject* _pObject)
{
		//! 오브젝트는 오브젝트 테이블에서 삭제한다.
		m_pPimple->m_tblObjectTable.erase(_pObject->GetObjectID());
}
OvObject*			OvObjectManager::FindObject(const OvObjectID& rObjHandle)
{
	if (m_pPimple->m_tblObjectTable.find(rObjHandle) != m_pPimple->m_tblObjectTable.end())
	{
		return m_pPimple->m_tblObjectTable[rObjHandle];
	}
	return NULL;
}