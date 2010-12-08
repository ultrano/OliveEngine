#include "OvObject.h"
#include "OvObjectManager.h"
#include "OvStringUtility.h"
#include "OvStorage.h"
#include "OvPropertyAccesser.h"
#include "OvRegisterableProperties.h"
#include "OliveValue.h"
#include "OvObjectProperties.h"
#include "OvStorage.h"

using namespace std;

OvRTTI_IMPL(OvObject);

OvPROPERTY_BAG_BEGIN(OvObject);
	OvPROPERTY_BAG_REGISTER( OvPropAccesser_STL_string, m_name );
	OvPROPERTY_BAG_REGISTER( OvPropAccesser_extra_data, m_extraPropertyTable );
OvPROPERTY_BAG_END(OvObject);

OvObject::OvObject()
{
	m_idObjectID = OvObjectManager::GetInstance()->AllocObjectID(this);
}
OvObject::~OvObject()
{
	ClearExtraProperties();
	OvObjectManager::GetInstance()->RecallObjectID(this);
}

void	OvObject::SetName( const OvChar* _pName )
{
	m_name = _pName;
}
const OvString& OvObject::GetName()
{
	return m_name;
}

OvObjectID		OvObject::GetObjectID()
{
	return m_idObjectID;
}

OvBool OvObject::AddExtraProperty( const OvString& propName, OliveValue::Value& extraProp )
{
	if ( m_extraPropertyTable.find( propName ) == m_extraPropertyTable.end() )
	{
		OliveValue::Value* copy = OliveValue::Factory( OvRTTI_Util::TypeName( &extraProp ) );
		if ( copy )
		{
			copy->CopyFrom( extraProp );
			m_extraPropertyTable[ propName ] = copy;
			return true;
		}
	}
	return false;
}

OvBool		OvObject::RemoveExtraProperty( const OvString& propName )
{
	extra_property_table::iterator tableIter = m_extraPropertyTable.find(propName) ;
	if ( m_extraPropertyTable.end() != tableIter )
	{
		m_extraPropertyTable.erase(tableIter);
		return true;
	}
	return false;
}
void		OvObject::ClearExtraProperties()
{
	m_extraPropertyTable.clear();
}

OliveValue::ValueSPtr OvObject::FindExtraProperty( const OvString& propName )
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
	OvObjectSPtr clone = Olive::CreateObject( OvRTTI_Util::TypeName( this ) );
	if ( clone )
	{
		OvObjectProperties objProp;
		ExtractProperties( this, objProp );
		InjectProperties( clone.GetRear(), objProp );
	}
	return clone;
}