#include "OvObject.h"
#include "OvObjectManager.h"
#include "OvStringUtility.h"
#include "OvStorage.h"
#include "OvProperty.h"
#include "OvRegisterableProperties.h"
#include <string>
using namespace std;

OvRTTI_IMPL(OvObject);

OvPROPERTY_BAG_BEGIN(OvObject);
	OvDECLARE_PROPERTY( OvProp_STL_string,  m_strObjectName);
OvPROPERTY_BAG_END(OvObject);

OvObject::OvObject()
{
	m_idObjectID = OvObjectManager::GetInstance()->AllocObjectID(this);
}
OvObject::OvObject(OvStorage& rStorage)
{

}
OvObject::~OvObject()
{
	OvObjectManager::GetInstance()->RecallObjectID(this);
}

void	OvObject::SetName(const char* _pName)
{
	m_strObjectName = _pName;
}
const char* OvObject::GetName()
{
	return m_strObjectName.data();
}

OvObjectID		OvObject::GetObjectID()
{
	return m_idObjectID;
}
