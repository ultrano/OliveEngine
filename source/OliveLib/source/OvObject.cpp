#include "OvObject.h"
#include "OvObjectManager.h"
#include "OvStringUtility.h"
#include "OvStorage.h"
#include "OvPropertyAccesser.h"
#include "OvRegisterableProperties.h"
#include "OliveValue.h"

#include <string>
using namespace std;

OvRTTI_IMPL(OvObject);

OvPROPERTY_BAG_BEGIN(OvObject);
	OvPROPERTY_BAG_REGISTER( OvPropAccesser_extra_data,  m_extraPropertyTable );
OvPROPERTY_BAG_END(OvObject);

OvObject::OvObject()
{
	m_idObjectID = OvObjectManager::GetInstance()->AllocObjectID(this);
	RegisterExtraProperty( "Name", OliveValue::Factory( "String" ) );
}
OvObject::OvObject(OvStorage& rStorage)
{
	m_idObjectID = OvObjectManager::GetInstance()->AllocObjectID(this);
}
OvObject::~OvObject()
{
	ClearExtraProperty();
	OvObjectManager::GetInstance()->RecallObjectID(this);
}

void	OvObject::SetName( const char* _pName )
{
	if ( OliveValue::Value* nameProp = FindExtraProperty( "Name" ) )
	{
		nameProp->SetValue( _pName );
	}
}
const string& OvObject::GetName()
{
	if ( OliveValue::Value* nameProp = FindExtraProperty( "Name" ) )
	{
		if ( OvRTTI_Util::IsTypeOf<OliveValue::String>( nameProp ) )
		{
			if ( OliveValue::String* name = static_cast<OliveValue::String*>( nameProp ) )
			{
				return name->GetString();
			}
		}
	}
	return "";
}

OvObjectID		OvObject::GetObjectID()
{
	return m_idObjectID;
}

void		OvObject::RegisterExtraProperty( const string& propName, OliveValue::Value* extraProp )
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
	}
	m_extraPropertyTable.clear();
}

OliveValue::Value* OvObject::FindExtraProperty( const string& propName )
{
	extra_property_table::iterator tableIter = m_extraPropertyTable.find(propName) ;
	if ( m_extraPropertyTable.end() != tableIter )
	{
		return tableIter->second;
	}
	return NULL;
}