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
	ClearExtraProperty();
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

void		OvObject::RegisterExtraProperty( const string& propName, OvExtraProperty::Value* extraProp )
{
	RemoveExtraProperty( propName );
	m_extraPropertyTable[propName] = extraProp;
}
bool		OvObject::RemoveExtraProperty( const string& propName )
{
	extra_property_table::iterator tableIter = m_extraPropertyTable.find(propName) ;
	if ( m_extraPropertyTable.end() != tableIter )
	{
		delete tableIter->second;
		m_extraPropertyTable.erase(tableIter);

		return true;
	}
	return false;
}
void		OvObject::ClearExtraProperty()
{
	for each( const extra_property_table_pair& propPair in m_extraPropertyTable )
	{
		delete propPair.second;
		m_extraPropertyTable.clear();
	}
}

OvExtraProperty::Value* OvObject::FindExtraProperty( const string& propName )
{
	extra_property_table::iterator tableIter = m_extraPropertyTable.find(propName) ;
	if ( m_extraPropertyTable.end() != tableIter )
	{
		return tableIter->second;
	}
	return NULL;
}