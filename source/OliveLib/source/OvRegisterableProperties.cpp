#include "OvRegisterableProperties.h"
#include "tinyxml.h"
#include "OvStringUtility.h"
#include "OvObjectProperties.h"
#include "OvObject.h"
#include "OvTransform.h"
#include "OliveValue.h"
#include "OvObjectCollector.h"
#include "OvAssociatedLinkConnector.h"
#include "OvResourceManager.h"
using namespace std;


////////////////////////////////////////////////////////////////////////////////////////////////
///////////////////////////				OvBool					/////////////////////////////
////////////////////////////////////////////////////////////////////////////////////////////////
OvRTTI_IMPL(OvPropAccesser_bool)
OvBool	OvPropAccesser_bool::Extract(OvObject* pObj, OvObjectProperties& rObjStore)
{
	if (pObj)
	{
		OvBool* kpProp = (OvBool*)Access(pObj);
		if ( kpProp )
		{
			OliveValue::Bool converter = *kpProp;
			rObjStore.PushValue( converter );

			return true;
		}
	}
	return false;
}
OvBool	OvPropAccesser_bool::Inject(OvObject* pObj, OvObjectProperties& rObjStore)
{
	if (pObj)
	{
		OvBool* kpProp = (OvBool*)Access(pObj);
		if (kpProp)
		{
			OliveValue::Bool converter;
			if ( rObjStore.PopValue( converter ) )
			{
				*kpProp = converter;
				return true;
			}		
		}
	}
	return false;
}

////////////////////////////////////////////////////////////////////////////////////////////////
///////////////////////////				Interger					/////////////////////////////
////////////////////////////////////////////////////////////////////////////////////////////////
OvRTTI_IMPL(OvPropAccesser_integer)
OvBool	OvPropAccesser_integer::Extract(OvObject* pObj, OvObjectProperties& rObjStore)
{
	if (pObj)
	{
		OvInt* kpProp = (OvInt*)Access(pObj);
		if (kpProp)
		{
			OliveValue::Integer converter = *kpProp;
			rObjStore.PushValue( converter );

			return true;
		}
	}
	return false;
}
OvBool	OvPropAccesser_integer::Inject(OvObject* pObj, OvObjectProperties& rObjStore)
{
	if (pObj)
	{
		OvInt* kpProp = (OvInt*)Access(pObj);
		if ( kpProp )
		{
			OliveValue::Integer converter;
			if (rObjStore.PopValue( converter ))
			{
				*kpProp = converter;
				return true;
			}
		}
	}
	return false;
}

////////////////////////////////////////////////////////////////////////////////////////////////
///////////////////////////				stl::OvString					/////////////////////////////
////////////////////////////////////////////////////////////////////////////////////////////////
OvRTTI_IMPL(OvPropAccesser_STL_string)
OvBool	OvPropAccesser_STL_string::Extract(OvObject* pObj, OvObjectProperties& rObjStore)
{
	if (pObj)
	{
		OvString* kpProp = (OvString*)Access(pObj);
		if (kpProp)
		{
			rObjStore.PushValue(*kpProp);
			return true;
		}
	}
	return false;
}
OvBool	OvPropAccesser_STL_string::Inject(OvObject* pObj, OvObjectProperties& rObjStore)
{
	if (pObj)
	{
		OvString* kpProp = (OvString*)Access(pObj);
		if (kpProp)
		{
			rObjStore.PopValue(*kpProp);
			return true;
		}
	}
	return false;
}

////////////////////////////////////////////////////////////////////////////////////////////////
///////////////////////////				object_pointer					/////////////////////////////
////////////////////////////////////////////////////////////////////////////////////////////////
OvRTTI_IMPL(OvPropAccesser_object_pointer)
OvBool	OvPropAccesser_object_pointer::Extract(OvObject* pObj, OvObjectProperties& rObjStore)
{
	OvObject** kpProp = (OvObject**)Access(pObj);
	if ( kpProp )
	{
		OliveValue::ObjectID extractValue;
		if ( *kpProp )
		{		
			extractValue.SetObjectID( (*kpProp)->GetObjectID() );
		}
		else
		{
			extractValue.SetObjectID( OvObjectID::INVALID );
		}
		rObjStore.PushValue(extractValue);
		rObjStore.PushAssociatedObject(*kpProp);
		return true;
	}
	return false;
}
OvBool	OvPropAccesser_object_pointer::Inject(OvObject* pObj, OvObjectProperties& rObjStore)
{
	OvObject** kpProp = (OvObject**)Access(pObj);
	if (kpProp)
	{
		OliveValue::ObjectID injectValue;
		if ( rObjStore.PopValue(injectValue) && injectValue.GetObjectID() != OvObjectID::INVALID )
		{
			OvPointerLinkConnector* linkBuilder = OvNew OvPointerLinkConnector;

			linkBuilder->SetFormerID( injectValue.GetObjectID() );
			linkBuilder->SetDestination( kpProp );

			rObjStore.CollectLinkBuilder( linkBuilder );

			return true;
		}
	}

	return false;
}

////////////////////////////////////////////////////////////////////////////////////////////////
///////////////////////////				object_smart_pointer					/////////////////////////////
////////////////////////////////////////////////////////////////////////////////////////////////
OvRTTI_IMPL(OvPropAccesser_object_smart_pointer)
OvBool	OvPropAccesser_object_smart_pointer::Extract(OvObject* pObj, OvObjectProperties& rObjStore)
{
	OvObjectSPtr* kpProp = (OvObjectSPtr*)Access(pObj);
	if (kpProp)
	{
		OliveValue::ObjectID extractValue;
		if ( (*kpProp) )
		{
			extractValue.SetObjectID( (*kpProp)->GetObjectID() );
		}
		else
		{
			extractValue.SetObjectID( OvObjectID::INVALID );
		}
		rObjStore.PushValue(extractValue);
		rObjStore.PushAssociatedObject( kpProp->GetRear() );
		return true;
	}
	return false;
}
OvBool	OvPropAccesser_object_smart_pointer::Inject(OvObject* pObj, OvObjectProperties& rObjStore)
{
	OvObjectSPtr* kpProp = (OvObjectSPtr*)Access(pObj);
	if (kpProp)
	{
		OliveValue::ObjectID injectValue;
		if ( rObjStore.PopValue(injectValue) && injectValue.GetObjectID() != OvObjectID::INVALID )
		{
			OvSmartPtrLinkConnector* linkBuilder = OvNew OvSmartPtrLinkConnector;

			linkBuilder->SetFormerID( injectValue.GetObjectID() );
			linkBuilder->SetSmartDestination( kpProp );			

			rObjStore.CollectLinkBuilder( linkBuilder );

			return true;
		}
	}

	return false;
}

////////////////////////////////////////////////////////////////////////////////////////////////
///////////////////////////				OvFloat					/////////////////////////////
////////////////////////////////////////////////////////////////////////////////////////////////
OvRTTI_IMPL(OvPropAccesser_float)
OvBool	OvPropAccesser_float::Extract(OvObject* pObj, OvObjectProperties& rObjStore)
{
	if (pObj)
	{
		OvFloat* kpProp = (OvFloat*)Access(pObj);
		if (kpProp)
		{
			OliveValue::Float converter = *kpProp;
			rObjStore.PushValue( converter );

			return true;
		}
	}
	return false;
}
OvBool	OvPropAccesser_float::Inject(OvObject* pObj, OvObjectProperties& rObjStore)
{
	if (pObj)
	{
		OvFloat* kpProp = (OvFloat*)Access(pObj);
		if (kpProp)
		{
			OliveValue::Float converter;
			if (rObjStore.PopValue( converter ))
			{
				*kpProp = converter;
				return true;
			}
		}
	}
	return false;
	return false;
}

////////////////////////////////////////////////////////////////////////////////////////////////
///////////////////////////				float2					/////////////////////////////
////////////////////////////////////////////////////////////////////////////////////////////////

OvRTTI_IMPL(OvPropAccesser_float2)
OvBool	OvPropAccesser_float2::Extract(OvObject* pObj, OvObjectProperties& rObjStore)
{
	OvFloat* kpProp = (OvFloat*)Access(pObj);
	if (kpProp)
	{
		OliveValue::Point2 converter = (const OvPoint2&)*kpProp;
		rObjStore.PushValue( converter );
		return true;
	}
	return false;
}
OvBool	OvPropAccesser_float2::Inject(OvObject* pObj, OvObjectProperties& rObjStore)
{
	OvFloat* kpProp = (OvFloat*)Access(pObj);
	if (kpProp)
	{
		OliveValue::Point2 converter;
		if ( rObjStore.PopValue( converter ) )
		{
			*(OvPoint2*)kpProp = converter;
			return true;
		}
	}
	return false;
}

////////////////////////////////////////////////////////////////////////////////////////////////
///////////////////////////				float3					/////////////////////////////
////////////////////////////////////////////////////////////////////////////////////////////////

OvRTTI_IMPL(OvPropAccesser_float3)
OvBool	OvPropAccesser_float3::Extract(OvObject* pObj, OvObjectProperties& rObjStore)
{
	OvFloat* kpProp = (OvFloat*)Access(pObj);
	if (kpProp)
	{
		OliveValue::Point3 converter = (const OvPoint3&)*kpProp;
		rObjStore.PushValue( converter );
		return true;
	}
	return false;
}
OvBool	OvPropAccesser_float3::Inject(OvObject* pObj, OvObjectProperties& rObjStore)
{
	OvFloat* kpProp = (OvFloat*)Access(pObj);
	if (kpProp)
	{
		OliveValue::Point3 converter;
		if ( rObjStore.PopValue( converter ) )
		{
			*(OvPoint3*)kpProp = converter;
		}
		return true;
	}
	return false;
}

////////////////////////////////////////////////////////////////////////////////////////////////
///////////////////////////				float4					/////////////////////////////
////////////////////////////////////////////////////////////////////////////////////////////////

OvRTTI_IMPL(OvPropAccesser_float4)
OvBool	OvPropAccesser_float4::Extract(OvObject* pObj, OvObjectProperties& rObjStore)
{
	OvFloat* kpProp = (OvFloat*)Access(pObj);
	if ( kpProp )
	{
		OliveValue::Quaternion converter = (const OvQuaternion&)*kpProp;
		rObjStore.PushValue( converter );
		return true;
	}
	return false;
}
OvBool	OvPropAccesser_float4::Inject(OvObject* pObj, OvObjectProperties& rObjStore)
{
	OvFloat* kpProp = (OvFloat*)Access(pObj);
	if ( kpProp )
	{
		OliveValue::Quaternion converter;
		if ( rObjStore.PopValue( converter ) )
		{		
			*(OvQuaternion*)kpProp = converter;
			return true;
		}
	}
	return false;
}

////////////////////////////////////////////////////////////////////////////////////////////////
///////////////////////////				transform					/////////////////////////////
////////////////////////////////////////////////////////////////////////////////////////////////

OvRTTI_IMPL(OvPropAccesser_transform)
OvBool	OvPropAccesser_transform::Extract(OvObject* pObj, OvObjectProperties& rObjStore)
{
	OvTransform* kpProp = (OvTransform*)Access(pObj);
	if (kpProp)
	{

		rObjStore.PushValue( OliveValue::Point3( kpProp->Scale ) );

		rObjStore.PushValue( OliveValue::Point3( kpProp->Position ) );

		rObjStore.PushValue( OliveValue::Quaternion( kpProp->Quaternion ) );

		return true;
	}
	return false;
}
OvBool	OvPropAccesser_transform::Inject(OvObject* pObj, OvObjectProperties& rObjStore)
{
	OvTransform* kpProp = (OvTransform*)Access(pObj);
	if (kpProp)
	{
		OliveValue::Point3 scale;
		OliveValue::Point3 position;
		OliveValue::Quaternion quat;

		rObjStore.PopValue( scale );
		rObjStore.PopValue( position );
		rObjStore.PopValue( quat );

		kpProp->Scale = scale;
		kpProp->Position = position;
		kpProp->Quaternion = quat;

		return true;
	}
	return false;
}


////////////////////////////////////////////////////////////////////////////////////////////////
///////////////////////////				extra					/////////////////////////////
////////////////////////////////////////////////////////////////////////////////////////////////

OvRTTI_IMPL(OvPropAccesser_extra_data)
OvBool	OvPropAccesser_extra_data::Extract(OvObject* pObj, OvObjectProperties& rObjStore)
{
	
	OvObject::extra_property_table* kpProp = (OvObject::extra_property_table*)Access(pObj);

	if (kpProp)
	{
		OvObject::extra_property_table& extraTable = *kpProp;

		OliveValue::Integer extraCount( (OvInt)extraTable.size() );
		
		unsigned savedPropCount = 0;
		OvString extraInfo;

		for each( const OvObject::extra_property_table_pair extraProp in extraTable )
		{
			OliveValue::Value* extraValue = (OliveValue::Value*)extraProp.second;

			OvString typeName = OvRTTI_Util::TypeName( extraValue );

			OliveValue::Integer typeLength( (OvInt)typeName.size() );
			OliveValue::Integer nameLength( (OvInt)extraProp.first.size() );
			OliveValue::Integer valueLength( (OvInt)extraValue->ToString().size() );

			if ( valueLength.GetInteger() )
			{
				// [9-5-1]somethingtest0
				// type: something
				// name: test
				// value: 0
				extraInfo += "[";
				extraInfo += typeLength.ToString();
				extraInfo += "-";
				extraInfo += nameLength.ToString();
				extraInfo += "-";
				extraInfo += valueLength.ToString();
				extraInfo += "]";
				extraInfo += typeName + extraProp.first + extraValue->ToString();

				++savedPropCount;
			}
		}

		extraInfo = OliveValue::Integer( savedPropCount ).ToString() + ":" + extraInfo;
		rObjStore.PushValue( extraInfo );

		return true;
	}
	return false;
}
OvBool	OvPropAccesser_extra_data::Inject(OvObject* pObj, OvObjectProperties& rObjStore)
{
	OvObject::extra_property_table* kpProp = (OvObject::extra_property_table*)Access(pObj);

	if (kpProp)
	{
		OvObject::extra_property_table& extraTable = *kpProp;

		OvString extraInfo;

		OvUInt count = 0;

		rObjStore.PopValue( extraInfo );

		sscanf_s( extraInfo.c_str(), "%d:%s", &count, &(extraInfo[0]), extraInfo.size() );

		OvString propInfo;
		propInfo = extraInfo;

		for ( unsigned i = 0 ; i < count ; ++i)
		{
			// [9-5-1]somethingtest0
			// type: something
			// name: test
			// value: 0
			OvUInt typeLength = 0;
			OvUInt nameLength = 0;
			OvUInt valueLength = 0;

			sscanf_s( propInfo.c_str(), "[%d-%d-%d]%s", &typeLength, &nameLength, &valueLength, &propInfo[0], propInfo.length() );

			OvString extra_type = propInfo;
			extra_type.resize( typeLength );

			OliveValue::Value*	extraValue = OliveValue::Factory( extra_type );
			if ( extraValue )
			{

				OvString extra_name = &( propInfo[ typeLength ] );
				OvString extra_value = &( propInfo[ typeLength + nameLength ] );

				extra_name.resize( nameLength );
				extra_value.resize( valueLength );

				extraValue->FromString( extra_value );

				extraTable[ extra_name ] = extraValue;
			}

			propInfo = &( propInfo[ typeLength + nameLength + valueLength ] );
		}
		return true;
	}
	return false;
}


////////////////////////////////////////////////////////////////////////////////////////////////
///////////////////////////				object_collector     		/////////////////////////////
////////////////////////////////////////////////////////////////////////////////////////////////

OvRTTI_IMPL(OvPropAccesser_object_collector);
OvBool OvPropAccesser_object_collector::Extract(OvObject* pObj, OvObjectProperties& rObjStore)
{
	if (pObj)
	{
		OvString collectedInfo;
		OvObjectCollector* kpProp = (OvObjectCollector*)Access(pObj);
		OliveValue::Integer relationCount( kpProp->Count() );

		collectedInfo += relationCount.ToString() + ":";

		for ( OvInt i = 0 ; i < relationCount.GetInteger() ; ++i )
		{
			OvObjectSPtr relatedObj = kpProp->GetByAt( i );
			if (relatedObj)
			{
				OliveValue::ObjectID relationID( relatedObj->GetObjectID() );
				collectedInfo += relationID.ToString() + "!";
				rObjStore.PushAssociatedObject( relatedObj.GetRear() );
			}
		}
		rObjStore.PushValue( collectedInfo );
		return true;
	}
	return false;
}
OvBool OvPropAccesser_object_collector::Inject(OvObject* pObj, OvObjectProperties& rObjStore)
{

	OvObjectCollector* kpProp = (OvObjectCollector*)Access(pObj);
	if (kpProp)
	{
		OvString data;
		OvUInt count = 0;

		rObjStore.PopValue( data );

		sscanf_s( data.c_str(), "%d:%s", &count, &data[0], data.size() );

		if ( count )
		{
			OvUInt id = 0;

			OvCollectedObjectsLinkConnector* linkBuilder = OvNew OvCollectedObjectsLinkConnector;

			linkBuilder->SetDestinateCollector( kpProp );

			for ( unsigned i = 0 ; i < count ; ++i)
			{
				sscanf_s( data.c_str(), "%d!%s", &id, &data[0], data.size() );
				OliveValue::ObjectID formerID( id );
				linkBuilder->AddRelatedObjectID( formerID.GetObjectID() );
			}

			rObjStore.CollectLinkBuilder( linkBuilder );
		}

		return true;

	}
	return false;
}


////////////////////////////////////////////////////////////////////////////////////////////////
///////////////////////////				resource     		/////////////////////////////
////////////////////////////////////////////////////////////////////////////////////////////////

OvRTTI_IMPL(OvPropAccesser_resource);

OvBool OvPropAccesser_resource::Extract( OvObject* pObj, OvObjectProperties& rObjStore )
{
	OvResourceSPtr* accessProp = (OvResourceSPtr*)Access(pObj);
	if ( accessProp )
	{
		OvString typeName = OvRTTI_Util::TypeName( (*accessProp) );
		OvString fileLocation = OvResourceManager::GetInstance()->FindFileLocation( (*accessProp) );
		ClampPathIfResDir( fileLocation );

		OvString resourceInfo;
		resourceInfo += typeName;
		resourceInfo += ":";
		resourceInfo += fileLocation;
		rObjStore.PushValue( resourceInfo );
		return true;
	}
	return false;
}

OvBool OvPropAccesser_resource::Inject( OvObject* pObj, OvObjectProperties& rObjStore )
{
	OvResourceSPtr* accessProp = (OvResourceSPtr*)Access(pObj);
	if ( accessProp )
	{
		OvString resourceInfo;
		OvString resourceType;
		OvString fileLocation;
		rObjStore.PopValue( resourceInfo );

		resourceType = resourceInfo;
		fileLocation = &(resourceInfo.at( resourceInfo.find(':') + 1 ));
		resourceType.resize( resourceInfo.find(':') );

		OvResourceSPtr resource = OvResourceManager::GetInstance()->LoadResource( resourceType, AbsolutePath( fileLocation ) );
		(*accessProp) = resource;
	}

	return false;
}

////////////////////////////////////////////////////////////////////////////////////////////////
///////////////////////////				resource_ticket     		/////////////////////////////
////////////////////////////////////////////////////////////////////////////////////////////////

OvRTTI_IMPL(OvPropAccesser_resource_ticket);

OvBool OvPropAccesser_resource_ticket::Extract( OvObject* pObj, OvObjectProperties& rObjStore )
{
	OvResourceTicketSPtr* accessProp = (OvResourceTicketSPtr*)Access(pObj);
	if ( accessProp )
	{
		OvResourceTicketSPtr ticket = (*accessProp);
		OvString typeName = ((OvRTTI*)ticket->GetResourceType())->TypeName();
		OvString fileLocation = ticket->GetFileName();
		ClampPathIfResDir( fileLocation );

		OvString resourceInfo;
		resourceInfo += typeName;
		resourceInfo += ":";
		resourceInfo += fileLocation;
		rObjStore.PushValue( resourceInfo );
		return true;
	}
	return false;
}

OvBool OvPropAccesser_resource_ticket::Inject( OvObject* pObj, OvObjectProperties& rObjStore )
{
	OvResourceTicketSPtr* accessProp = (OvResourceTicketSPtr*)Access(pObj);
	if ( accessProp )
	{
		OvString resourceInfo;
		OvString resourceType;
		OvString fileLocation;
		rObjStore.PopValue( resourceInfo );

		resourceType = resourceInfo;
		fileLocation = &(resourceInfo.at( resourceInfo.find(':') + 1 ));
		resourceType.resize( resourceInfo.find(':') );

		(*accessProp) = OvResourceManager::GetInstance()->AsyncLoadResource( resourceType, AbsolutePath( fileLocation ) );
		
	}

	return false;
}