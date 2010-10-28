#include "OvRegisterableProperties.h"
#include <string>
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
///////////////////////////				bool					/////////////////////////////
////////////////////////////////////////////////////////////////////////////////////////////////
OvRTTI_IMPL(OvPropAccesser_bool)
bool	OvPropAccesser_bool::Extract(OvObject* pObj, OvObjectProperties& rObjStore)
{
	if (pObj)
	{
		bool* kpProp = (bool*)Access(pObj);
		if ( kpProp )
		{
			OliveValue::Bool converter = *kpProp;
			rObjStore.PushValue( converter );

			return true;
		}
	}
	return false;
}
bool	OvPropAccesser_bool::Inject(OvObject* pObj, OvObjectProperties& rObjStore)
{
	if (pObj)
	{
		bool* kpProp = (bool*)Access(pObj);
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
bool	OvPropAccesser_integer::Extract(OvObject* pObj, OvObjectProperties& rObjStore)
{
	if (pObj)
	{
		int* kpProp = (int*)Access(pObj);
		if (kpProp)
		{
			OliveValue::Integer converter = *kpProp;
			rObjStore.PushValue( converter );

			return true;
		}
	}
	return false;
}
bool	OvPropAccesser_integer::Inject(OvObject* pObj, OvObjectProperties& rObjStore)
{
	if (pObj)
	{
		int* kpProp = (int*)Access(pObj);
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
///////////////////////////				stl::string					/////////////////////////////
////////////////////////////////////////////////////////////////////////////////////////////////
OvRTTI_IMPL(OvPropAccesser_STL_string)
bool	OvPropAccesser_STL_string::Extract(OvObject* pObj, OvObjectProperties& rObjStore)
{
	if (pObj)
	{
		string* kpProp = (string*)Access(pObj);
		if (kpProp)
		{
			rObjStore.PushValue(*kpProp);
			return true;
		}
	}
	return false;
}
bool	OvPropAccesser_STL_string::Inject(OvObject* pObj, OvObjectProperties& rObjStore)
{
	if (pObj)
	{
		string* kpProp = (string*)Access(pObj);
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
bool	OvPropAccesser_object_pointer::Extract(OvObject* pObj, OvObjectProperties& rObjStore)
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
bool	OvPropAccesser_object_pointer::Inject(OvObject* pObj, OvObjectProperties& rObjStore)
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
bool	OvPropAccesser_object_smart_pointer::Extract(OvObject* pObj, OvObjectProperties& rObjStore)
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
bool	OvPropAccesser_object_smart_pointer::Inject(OvObject* pObj, OvObjectProperties& rObjStore)
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
///////////////////////////				float					/////////////////////////////
////////////////////////////////////////////////////////////////////////////////////////////////
OvRTTI_IMPL(OvPropAccesser_float)
bool	OvPropAccesser_float::Extract(OvObject* pObj, OvObjectProperties& rObjStore)
{
	if (pObj)
	{
		float* kpProp = (float*)Access(pObj);
		if (kpProp)
		{
			OliveValue::Float converter = *kpProp;
			rObjStore.PushValue( converter );

			return true;
		}
	}
	return false;
}
bool	OvPropAccesser_float::Inject(OvObject* pObj, OvObjectProperties& rObjStore)
{
	if (pObj)
	{
		float* kpProp = (float*)Access(pObj);
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
bool	OvPropAccesser_float2::Extract(OvObject* pObj, OvObjectProperties& rObjStore)
{
	float* kpProp = (float*)Access(pObj);
	if (kpProp)
	{
		OliveValue::Point2 converter = (const OvPoint2&)*kpProp;
		rObjStore.PushValue( converter );
		return true;
	}
	return false;
}
bool	OvPropAccesser_float2::Inject(OvObject* pObj, OvObjectProperties& rObjStore)
{
	float* kpProp = (float*)Access(pObj);
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
bool	OvPropAccesser_float3::Extract(OvObject* pObj, OvObjectProperties& rObjStore)
{
	float* kpProp = (float*)Access(pObj);
	if (kpProp)
	{
		OliveValue::Point3 converter = (const OvPoint3&)*kpProp;
		rObjStore.PushValue( converter );
		return true;
	}
	return false;
}
bool	OvPropAccesser_float3::Inject(OvObject* pObj, OvObjectProperties& rObjStore)
{
	float* kpProp = (float*)Access(pObj);
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
bool	OvPropAccesser_float4::Extract(OvObject* pObj, OvObjectProperties& rObjStore)
{
	float* kpProp = (float*)Access(pObj);
	if ( kpProp )
	{
		OliveValue::Quaternion converter = (const OvQuaternion&)*kpProp;
		rObjStore.PushValue( converter );
		return true;
	}
	return false;
}
bool	OvPropAccesser_float4::Inject(OvObject* pObj, OvObjectProperties& rObjStore)
{
	float* kpProp = (float*)Access(pObj);
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
bool	OvPropAccesser_transform::Extract(OvObject* pObj, OvObjectProperties& rObjStore)
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
bool	OvPropAccesser_transform::Inject(OvObject* pObj, OvObjectProperties& rObjStore)
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
bool	OvPropAccesser_extra_data::Extract(OvObject* pObj, OvObjectProperties& rObjStore)
{
	
	OvObject::extra_property_table* kpProp = (OvObject::extra_property_table*)Access(pObj);

	if (kpProp)
	{
		OvObject::extra_property_table& extraTable = *kpProp;

		OliveValue::Integer extraCount( (int)extraTable.size() );
		
		unsigned savedPropCount = 0;
		string extraInfo;

		for each( const OvObject::extra_property_table_pair extraProp in extraTable )
		{
			OliveValue::Value* extraValue = (OliveValue::Value*)extraProp.second;

			string typeName = OvRTTI_Util::TypeName( extraValue );

			OliveValue::Integer typeLength( (int)typeName.size() );
			OliveValue::Integer nameLength( (int)extraProp.first.size() );
			OliveValue::Integer valueLength( (int)extraValue->GetValue().size() );

			if ( valueLength.GetInteger() )
			{
				// [9-5-1]somethingtest0
				// type: something
				// name: test
				// value: 0
				extraInfo += "[";
				extraInfo += typeLength.GetValue();
				extraInfo += "-";
				extraInfo += nameLength.GetValue();
				extraInfo += "-";
				extraInfo += valueLength.GetValue();
				extraInfo += "]";
				extraInfo += typeName + extraProp.first + extraValue->GetValue();

				++savedPropCount;
			}
		}

		extraInfo = OliveValue::Integer( savedPropCount ).GetValue() + ":" + extraInfo;
		rObjStore.PushValue( extraInfo );

		return true;
	}
	return false;
}
bool	OvPropAccesser_extra_data::Inject(OvObject* pObj, OvObjectProperties& rObjStore)
{
	OvObject::extra_property_table* kpProp = (OvObject::extra_property_table*)Access(pObj);

	if (kpProp)
	{
		OvObject::extra_property_table& extraTable = *kpProp;

		string extraInfo;

		unsigned int count = 0;

		rObjStore.PopValue( extraInfo );

		sscanf_s( extraInfo.c_str(), "%d:%s", &count, &(extraInfo[0]), extraInfo.size() );

		string propInfo;
		propInfo = extraInfo;

		for ( unsigned i = 0 ; i < count ; ++i)
		{
			// [9-5-1]somethingtest0
			// type: something
			// name: test
			// value: 0
			unsigned int typeLength = 0;
			unsigned int nameLength = 0;
			unsigned int valueLength = 0;

			sscanf_s( propInfo.c_str(), "[%d-%d-%d]%s", &typeLength, &nameLength, &valueLength, &propInfo[0], propInfo.length() );

			string extra_type = propInfo;
			extra_type.resize( typeLength );

			OliveValue::Value*	extraValue = OliveValue::Factory( extra_type );
			if ( extraValue )
			{

				string extra_name = &( propInfo[ typeLength ] );
				string extra_value = &( propInfo[ typeLength + nameLength ] );

				extra_name.resize( nameLength );
				extra_value.resize( valueLength );

				extraValue->SetValue( extra_value );

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
bool OvPropAccesser_object_collector::Extract(OvObject* pObj, OvObjectProperties& rObjStore)
{
	if (pObj)
	{
		string collectedInfo;
		OvObjectCollector* kpProp = (OvObjectCollector*)Access(pObj);
		OliveValue::Integer relationCount( kpProp->Count() );

		collectedInfo += relationCount.GetValue() + ":";

		for ( int i = 0 ; i < relationCount.GetInteger() ; ++i )
		{
			OvObjectSPtr relatedObj = kpProp->GetByAt( i );
			if (relatedObj)
			{
				OliveValue::ObjectID relationID( relatedObj->GetObjectID() );
				collectedInfo += relationID.GetValue() + "!";
				rObjStore.PushAssociatedObject( relatedObj.GetRear() );
			}
		}
		rObjStore.PushValue( collectedInfo );
		return true;
	}
	return false;
}
bool OvPropAccesser_object_collector::Inject(OvObject* pObj, OvObjectProperties& rObjStore)
{

	OvObjectCollector* kpProp = (OvObjectCollector*)Access(pObj);
	if (kpProp)
	{
		string data;
		unsigned int count = 0;

		rObjStore.PopValue( data );

		sscanf_s( data.c_str(), "%d:%s", &count, &data[0], data.size() );

		if ( count )
		{
			unsigned int id = 0;

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

bool OvPropAccesser_resource::Extract( OvObject* pObj, OvObjectProperties& rObjStore )
{
	OvResourceSPtr* accessProp = (OvResourceSPtr*)Access(pObj);
	if ( accessProp )
	{
		string typeName = OvRTTI_Util::TypeName( (*accessProp) );
		string fileLocation = OvResourceManager::GetInstance()->FindFileLocation( (*accessProp) );
		ClampPathIfResDir( fileLocation );

		string resourceInfo;
		resourceInfo += typeName;
		resourceInfo += ":";
		resourceInfo += fileLocation;
		rObjStore.PushValue( resourceInfo );
		return true;
	}
	return false;
}

bool OvPropAccesser_resource::Inject( OvObject* pObj, OvObjectProperties& rObjStore )
{
	OvResourceSPtr* accessProp = (OvResourceSPtr*)Access(pObj);
	if ( accessProp )
	{
		string resourceInfo;
		string resourceType;
		string fileLocation;
		rObjStore.PopValue( resourceInfo );

		resourceType = resourceInfo;
		fileLocation = &(resourceInfo.at( resourceInfo.find(':') + 1 ));
		resourceType.resize( resourceInfo.find(':') );

		OvResourceSPtr resource = OvResourceManager::GetInstance()->LoadResource( resourceType, ResDirPath( fileLocation ) );
		(*accessProp) = resource;
	}

	return false;
}

////////////////////////////////////////////////////////////////////////////////////////////////
///////////////////////////				resource_ticket     		/////////////////////////////
////////////////////////////////////////////////////////////////////////////////////////////////

OvRTTI_IMPL(OvPropAccesser_resource_ticket);

bool OvPropAccesser_resource_ticket::Extract( OvObject* pObj, OvObjectProperties& rObjStore )
{
	OvResourceTicketSPtr* accessProp = (OvResourceTicketSPtr*)Access(pObj);
	if ( accessProp )
	{
		OvResourceTicketSPtr ticket = (*accessProp);
		OvResourceSPtr resource = ticket->CheckOut();
		string typeName = OvRTTI_Util::TypeName( resource );
		string fileLocation = OvResourceManager::GetInstance()->FindFileLocation( resource );
		ClampPathIfResDir( fileLocation );

		string resourceInfo;
		resourceInfo += typeName;
		resourceInfo += ":";
		resourceInfo += fileLocation;
		rObjStore.PushValue( resourceInfo );
		return true;
	}
	return false;
}

bool OvPropAccesser_resource_ticket::Inject( OvObject* pObj, OvObjectProperties& rObjStore )
{
	OvResourceTicketSPtr* accessProp = (OvResourceTicketSPtr*)Access(pObj);
	if ( accessProp )
	{
		string resourceInfo;
		string resourceType;
		string fileLocation;
		rObjStore.PopValue( resourceInfo );

		resourceType = resourceInfo;
		fileLocation = &(resourceInfo.at( resourceInfo.find(':') + 1 ));
		resourceType.resize( resourceInfo.find(':') );

		(*accessProp) = OvResourceManager::GetInstance()->CheckTicket( ResDirPath( fileLocation )  );

		OvResourceSPtr resource = OvResourceManager::GetInstance()->LoadResource( resourceType, ResDirPath( fileLocation ) );
	}

	return false;
}