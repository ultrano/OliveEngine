#include "OvStoreObject.h"
#include "tinyxml.h"
#include <string>

OvRTTI_IMPL_NOPARENT(OvStoreObject);

struct OvStoreObject::OvPimple : OvMemObject
{
	string	m_strName;
};
OvStoreObject::OvStoreObject()
:m_pPimple(OvNew OvStoreObject::OvPimple)
{

}
OvStoreObject::~OvStoreObject()
{

}

void		OvStoreObject::SetName(const char* pName)
{
	if (pName)
	{
		m_pPimple->m_strName = pName;
	}
}
const char* OvStoreObject::GetName()
{
	return m_pPimple->m_strName.data();
}