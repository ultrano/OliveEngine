#include "OvObject.h"
#include "OvObjectManager.h"
#include "OvStringUtility.h"
#include "OvProperty.h"
#include <string>
using namespace std;

OvRTTI_IMPL_PROP(OvObject,OvRefBase);
OvPROP_BAG_IMPL(OvObject);

void OvObject::RegisterProperties()
{
};

OvObject::OvObject()
{
	m_idObjectID = OvObjectManager::GetInstance()->AllocObjectID(this);
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

const OvObjectID		OvObject::GetObjectID()
{
	return m_idObjectID;
}