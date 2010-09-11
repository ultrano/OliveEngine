#include "OvRegisterableProperties.h"
#include <string>
#include "tinyxml.h"
#include "OvStringUtility.h"
#include "OvObjectProperties.h"
#include "OvObject.h"
#include "OvTransform.h"
#include "OliveValue.h"
#include "OvObjectCollector.h"
#include "OvRelationLinkBuilder.h"
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
		if (kpProp)
		{
			rObjStore.PushValue((*kpProp)?"1":"0");

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
			string kstrValue;
			if (rObjStore.PopValue(kstrValue))
			{
				*kpProp = (string("1") == kstrValue);
			}
		
			return true;
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
			string kstrValue = OvFormatString("%d",*kpProp);
			rObjStore.PushValue(kstrValue);

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
		if (kpProp)
		{
			string kstrValue;
			if (rObjStore.PopValue(kstrValue))
			{
				sscanf_s(kstrValue.data(),"%d",kpProp);
			}

			return true;
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
		if (*kpProp )
		{		
			extractValue.SetObjectID( (*kpProp)->GetObjectID() );
		}
		else
		{
			extractValue.SetObjectID( OvObjectID::INVALID );
		}
		rObjStore.PushValue(extractValue);
		rObjStore.PushComponentObject(*kpProp);
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
			OvPointLinkBuilder* linkBuilder = OvNew OvPointLinkBuilder;

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
		rObjStore.PushComponentObject( kpProp->GetRear() );
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
			OvSmartLinkBuilder* linkBuilder = OvNew OvSmartLinkBuilder;

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
			OliveValue::Float extractValue;
			extractValue.SetFloat(*kpProp);
			rObjStore.PushValue(extractValue);

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
			OliveValue::Float extractValue;
			if (rObjStore.PopValue(extractValue))
			{
				*kpProp = extractValue.GetFloat();
			}

			return true;
		}
	}
	return false;
	return false;
}

////////////////////////////////////////////////////////////////////////////////////////////////
///////////////////////////				float2					/////////////////////////////
////////////////////////////////////////////////////////////////////////////////////////////////
#define float2_to_string(_float,_string) (_string = string(OvFormatString("%f %f",((_float)[0]),((_float)[1]))))
#define string_to_float2(_string,_float) (sscanf_s(_string.data(),"%f %f",&((_float)[0]),&((_float)[1])))

OvRTTI_IMPL(OvPropAccesser_float2)
bool	OvPropAccesser_float2::Extract(OvObject* pObj, OvObjectProperties& rObjStore)
{
	float* kpProp = (float*)Access(pObj);
	if (kpProp)
	{
		OliveValue::Point2 extractValue;
		extractValue.SetPoint2( (const OvPoint2&)*kpProp );
		rObjStore.PushValue(extractValue);
		return true;
	}
	return false;
}
bool	OvPropAccesser_float2::Inject(OvObject* pObj, OvObjectProperties& rObjStore)
{
	float* kpProp = (float*)Access(pObj);
	if (kpProp)
	{
		OliveValue::Point2 injectValue;
		rObjStore.PopValue(injectValue);
		*(OvPoint2*)kpProp = injectValue.GetPoint2();
		return true;
	}
	return false;
}

////////////////////////////////////////////////////////////////////////////////////////////////
///////////////////////////				float3					/////////////////////////////
////////////////////////////////////////////////////////////////////////////////////////////////
#define float3_to_string(_float,_string) (_string = string(OvFormatString("%f %f %f",((_float)[0]),((_float)[1]),((_float)[2]))))
#define string_to_float3(_string,_float) (sscanf_s(_string.data(),"%f %f %f",&((_float)[0]),&((_float)[1]),&((_float)[2])))

OvRTTI_IMPL(OvPropAccesser_float3)
bool	OvPropAccesser_float3::Extract(OvObject* pObj, OvObjectProperties& rObjStore)
{
	float* kpProp = (float*)Access(pObj);
	if (kpProp)
	{
		OliveValue::Point3 extractValue;
		extractValue.SetPoint3( (const OvPoint3&)*kpProp );
		rObjStore.PushValue( extractValue );
		return true;
	}
	return false;
}
bool	OvPropAccesser_float3::Inject(OvObject* pObj, OvObjectProperties& rObjStore)
{
	float* kpProp = (float*)Access(pObj);
	if (kpProp)
	{
		OliveValue::Point3 injectValue;
		rObjStore.PopValue( injectValue );
		*(OvPoint3*)kpProp = injectValue.GetPoint3();
		return true;
	}
	return false;
}

////////////////////////////////////////////////////////////////////////////////////////////////
///////////////////////////				float4					/////////////////////////////
////////////////////////////////////////////////////////////////////////////////////////////////
#define float4_to_string(_float,_string) (_string = string(OvFormatString("%f %f %f %f",((_float)[0]),((_float)[1]),((_float)[2]),((_float)[3]))))
#define string_to_float4(_string,_float) (sscanf_s(_string.data(),"%f %f %f %f",&((_float)[0]),&((_float)[1]),&((_float)[2]),&((_float)[3])))

OvRTTI_IMPL(OvPropAccesser_float4)
bool	OvPropAccesser_float4::Extract(OvObject* pObj, OvObjectProperties& rObjStore)
{
	float* kpProp = (float*)Access(pObj);
	if (kpProp)
	{
		OliveValue::Quaternion extractValue;
		extractValue.SetQuaternion( (const OvQuaternion&)*kpProp );
		rObjStore.PushValue(extractValue);
		return true;
	}
	return false;
}
bool	OvPropAccesser_float4::Inject(OvObject* pObj, OvObjectProperties& rObjStore)
{
	float* kpProp = (float*)Access(pObj);
	if (kpProp)
	{
		OliveValue::Quaternion injectValue;
		rObjStore.PopValue(injectValue);
		*(OvQuaternion*)kpProp = injectValue.GetQuaternion();
		return true;
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
		string kstrValue;

		float3_to_string(&(kpProp->Scale),kstrValue);
		rObjStore.PushValue(kstrValue);

		float3_to_string(&(kpProp->Position),kstrValue);
		rObjStore.PushValue(kstrValue);

		float4_to_string(&(kpProp->Quaternion),kstrValue);
		rObjStore.PushValue(kstrValue);

		return true;
	}
	return false;
}
bool	OvPropAccesser_transform::Inject(OvObject* pObj, OvObjectProperties& rObjStore)
{
	OvTransform* kpProp = (OvTransform*)Access(pObj);
	if (kpProp)
	{
		string kstrValue;

		rObjStore.PopValue(kstrValue);
		string_to_float3(kstrValue,	&(kpProp->Scale));

		rObjStore.PopValue(kstrValue);
		string_to_float3(kstrValue,	&(kpProp->Position));

		rObjStore.PopValue(kstrValue);
		string_to_float3(kstrValue,	&(kpProp->Quaternion));

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

		OliveValue::Integer extraCount( extraTable.size() );
		
		unsigned savedPropCount = 0;
		string extraInfo;

		for each( const OvObject::extra_property_table_pair extraProp in extraTable )
		{
			OliveValue::Value* extraValue = (OliveValue::Value*)extraProp.second;

			string typeName = OvRTTI_Util::TypeName( extraValue );

			OliveValue::Integer typeLength( typeName.size() );
			OliveValue::Integer nameLength( extraProp.first.size() );
			OliveValue::Integer valueLength( extraValue->GetValue().size() );

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

		sscanf( extraInfo.c_str(), "%d:%s", &count, &extraInfo[0] );

		string propInfo;
		propInfo = extraInfo;

		for (int i = 0 ; i < count ; ++i)
		{
			// [9-5-1]somethingtest0
			// type: something
			// name: test
			// value: 0
			unsigned int typeLength = 0;
			unsigned int nameLength = 0;
			unsigned int valueLength = 0;

			sscanf( propInfo.c_str(), "[%d-%d-%d]%s", &typeLength, &nameLength, &valueLength, &propInfo[0] );

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
				rObjStore.PushComponentObject( relatedObj.GetRear() );
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

		sscanf( data.c_str(), "%d:%s", &count, &data[0] );

		if ( count )
		{
			unsigned int id = 0;

			OvObjectCollectorLinkBuilder* linkBuilder = OvNew OvObjectCollectorLinkBuilder;

			linkBuilder->SetDestinateCollector( kpProp );

			for (int i = 0 ; i < count ; ++i)
			{
				sscanf( data.c_str(), "%d!%s", &id, &data[0] );
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
	if ( accessProp && (*accessProp) )
	{
		string typeName = OvRTTI_Util::TypeName( (*accessProp) );
		string fileLocation = OvResourceManager::GetInstance()->FindFileLocation( (*accessProp).GetRear() );

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

		OvResourceSPtr resource = OvResourceManager::GetInstance()->LoadResource( resourceType, fileLocation);
		(*accessProp) = resource;
	}

	return false;
}