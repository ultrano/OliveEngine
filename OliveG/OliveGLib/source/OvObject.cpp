#include "OvObject.h"
#include "OvObjectManager.h"
#include "OvStringUtility.h"
#include "OvStorage.h"
#include "OvProperty.h"
#include "OvRegisterableProperties.h"
#include <string>
using namespace std;

OvRTTI_IMPL_PROP(OvObject,OvRefBase);
OvPROP_BAG_IMPL(OvObject);

void OvObject::RegisterProperties()
{
	OvProperty* kpProp = NULL;

	kpProp = new OvProp_STL_string;
	kpProp->SetOffset(offsetof(__this_class,m_strObjectName));
	kpProp->SetPropertyName("m_strObjectName");
	GetPropertyBag()->RegisterProperty(kpProp);
};

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

const OvObjectID		OvObject::GetObjectID()
{
	return m_idObjectID;
}
void	OvObject::CallByFactory(OvStorage& rStorage)
{
	rStorage;
}