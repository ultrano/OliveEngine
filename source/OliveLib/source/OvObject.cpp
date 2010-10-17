#include "OvObject.h"
#include "OvObjectManager.h"
#include "OvStringUtility.h"
#include "OvStorage.h"
#include "OvPropertyAccesser.h"
#include "OvRegisterableProperties.h"
#include "OliveValue.h"
#include "OvObjectProperties.h"
#include "OvStorage.h"

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
void ExtractProperties( OvObject* obj, OvObjectProperties& prop )
{
	if ( OvRTTI_Util::IsKindOf<OvObject>( obj ) )
	{
		for ( OvRTTI * rtti = const_cast<OvRTTI*>(obj->QueryRTTI())
			; NULL != rtti
			; rtti = const_cast<OvRTTI*>(rtti->GetBaseRTTI()))
		{
			OvPropertyBag* prop_bag = rtti->PropertyBag();
			if (prop_bag)
			{
				OvPropertyAccesser* prop_acces = NULL;
				for ( unsigned i = 0 ; prop_acces = prop_bag->GetPropertyAt( i ) ; ++i )
				{
					prop_acces->Extract( obj, prop );
				}
			}		
		}
	}

}

void InjectProperties( OvObject* obj, OvObjectProperties& prop )
{
	if ( OvRTTI_Util::IsKindOf<OvObject>( obj ) )
	{
		for ( OvRTTI * rtti = const_cast<OvRTTI*>(obj->QueryRTTI())
			; NULL != rtti
			; rtti = const_cast<OvRTTI*>(rtti->GetBaseRTTI()))
		{
			OvPropertyBag* prop_bag = rtti->PropertyBag();
			if (prop_bag)
			{
				OvPropertyAccesser* prop_acces = NULL;
				for ( unsigned i = 0 ; prop_acces = prop_bag->GetPropertyAt( i ) ; ++i )
				{
					prop_acces->Inject( obj, prop );
				}
			}		
		}
	}
}

OvObjectSPtr OvObject::Clone()
{
	OvObjectSPtr clone = TemporaryFactoryFunction( OvRTTI_Util::TypeName( this ));
	if ( clone )
	{
		OvObjectProperties objProp;
		ExtractProperties( this, objProp );
		InjectProperties( clone.GetRear(), objProp );
	}
	return clone;
}