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

OvObject::OvObject()
{
	m_idObjectID = OvObjectManager::GetInstance()->AllocObjectID(this);
}
OvObject::~OvObject()
{
	OvObjectManager::GetInstance()->RecallObjectID(this);
}

OvObjectID		OvObject::GetObjectID()
{
	return m_idObjectID;
}

void ExtractProperties( OvObject* obj, OvObjectProperties& prop )
{
	if ( OvIsKindOf<OvObject>( obj ) )
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
	if ( OvIsKindOf<OvObject>( obj ) )
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
	OvObjectSPtr clone = Olive::CreateObject( OvTypeName( this ) );
	if ( clone )
	{
		OvObjectProperties objProp;
		ExtractProperties( this, objProp );
		InjectProperties( clone.GetRear(), objProp );
	}
	return clone;
}

OvObjectSPtr OvObject::CustomClone()
{
	return Clone();
}