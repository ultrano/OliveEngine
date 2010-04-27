#include "OvStorage.h"
#include "OvObjectCollector.h"
#include "OvStringUtility.h"
#include "OvObjectFactory.h"
struct OvStorage::OvPimple : OvMemObject
{
	OvObjectCollector	m_cltStoreCollector;
	OvObjectCollector	m_cltRestoreCollector;
};


OvStorage::OvStorage()
:m_pPimple(OvNew OvStorage::OvPimple)
{

}
OvStorage::~OvStorage()
{

}
void	OvStorage::Store(const char* pFile)
{
}
void	OvStorage::Restore(const char* pFile)
{
}
void	OvStorage::RegisterObject(OvObjectSPtr _pObj)
{

}
void	OvStorage::RemoveObject(OvObjectSPtr _pObj)
{
}