#include "OvStoreData.h"

OvRTTI_IMPL(OvStoreData);
struct OvStoreData::OvPimple : OvMemObject
{
	string	m_strDataString;
	string	m_strDataType;
};

OvStoreData::OvStoreData()
:m_pPimple(OvNew OvStoreData::OvPimple)
{

}
OvStoreData::OvStoreData(const char* pName)
:m_pPimple(OvNew OvStoreData::OvPimple)
{
	SetName(pName);
}
OvStoreData::~OvStoreData()
{

}

void		OvStoreData::SetDataString(const char* pData)
{
	if (pData)
	{
		m_pPimple->m_strDataString = pData;
	}
}
const char* OvStoreData::GetDataString()
{
	return m_pPimple->m_strDataString.data();
}

void		OvStoreData::SetDataType(const char* pType)
{
	if (pType)
	{
		m_pPimple->m_strDataType = pType;
	}
}
const char* OvStoreData::GetDataType()
{
	return m_pPimple->m_strDataType.data();
}
OvStoreObject*	OvStoreData::MakeCopyInstance()
{
	OvStoreData* kpCopy = OvNew OvStoreData;
	if (CopyTo(kpCopy))
	{
		return kpCopy;
	}
	OvDelete kpCopy;
	return NULL;
}
bool			OvStoreData::CopyTo(OvStoreObject* pObj)
{
	if ( OvRTTI_Util::IsTypeOf< OvStoreData >( pObj ) )
	{
		OvStoreData* pData = (OvStoreData*)pObj;
		pData->m_pPimple->m_strDataString	= m_pPimple->m_strDataString;
		pData->m_pPimple->m_strDataType	=	m_pPimple->m_strDataType;
		return true;
	}
	return false;
}