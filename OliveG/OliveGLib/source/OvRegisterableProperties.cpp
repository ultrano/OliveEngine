#include "OvRegisterableProperties.h"
#include <string>
#include "tinyxml.h"
#include "OvStringUtility.h"
#include "OvObjectProperties.h"
#include "OvObject.h"
#include "OvTransform.h"
#include "OliveValue.h"
using namespace std;


////////////////////////////////////////////////////////////////////////////////////////////////
///////////////////////////				bool					/////////////////////////////
////////////////////////////////////////////////////////////////////////////////////////////////
OvRTTI_IMPL(OvProp_bool)
bool	OvProp_bool::Extract(OvObject* pObj, OvObjectProperties& rObjStore)
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
bool	OvProp_bool::Inject(OvObject* pObj, OvObjectProperties& rObjStore)
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
OvRTTI_IMPL(OvProp_integer)
bool	OvProp_integer::Extract(OvObject* pObj, OvObjectProperties& rObjStore)
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
bool	OvProp_integer::Inject(OvObject* pObj, OvObjectProperties& rObjStore)
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
OvRTTI_IMPL(OvProp_STL_string)
bool	OvProp_STL_string::Extract(OvObject* pObj, OvObjectProperties& rObjStore)
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
bool	OvProp_STL_string::Inject(OvObject* pObj, OvObjectProperties& rObjStore)
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
///////////////////////////				object					/////////////////////////////
////////////////////////////////////////////////////////////////////////////////////////////////
OvRTTI_IMPL(OvProp_ObjectPtr)
bool	OvProp_ObjectPtr::Extract(OvObject* pObj, OvObjectProperties& rObjStore)
{
	OvObject* kpProp = (OvObject*)Access(pObj);
	if (kpProp)
	{
		string kstrValue = OvFormatString("%I64d",kpProp->GetObjectID());
		rObjStore.PushValue(kstrValue);
		rObjStore.PushComponentObject(kpProp);
		return true;
	}
	return false;
}
bool	OvProp_ObjectPtr::Inject(OvObject* pObj, OvObjectProperties& rObjStore)
{
	OvObject** kpProp = (OvObject**)Access(pObj);
	if (kpProp)
	{
		string kstrValue;
		if (rObjStore.PopValue(kstrValue))
		{
			SComponentLinkInfo linkInfo;
			sscanf_s(kstrValue.c_str(),"%I64d",&linkInfo.formerID);
			linkInfo.linkDestination = kpProp;
			rObjStore.PushComponentLinkInfo(linkInfo);

			return true;
		}
	}

	return false;
}

////////////////////////////////////////////////////////////////////////////////////////////////
///////////////////////////				float					/////////////////////////////
////////////////////////////////////////////////////////////////////////////////////////////////
OvRTTI_IMPL(OvProp_float)
bool	OvProp_float::Extract(OvObject* pObj, OvObjectProperties& rObjStore)
{
	if (pObj)
	{
		float* kpProp = (float*)Access(pObj);
		if (kpProp)
		{
			string kstrValue = OvFormatString("%f",*kpProp);
			rObjStore.PushValue(kstrValue);

			return true;
		}
	}
	return false;
}
bool	OvProp_float::Inject(OvObject* pObj, OvObjectProperties& rObjStore)
{
	if (pObj)
	{
		float* kpProp = (float*)Access(pObj);
		if (kpProp)
		{
			string kstrValue;
			if (rObjStore.PopValue(kstrValue))
			{
				sscanf_s(kstrValue.data(),"%f",kpProp);
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

OvRTTI_IMPL(OvProp_float2)
bool	OvProp_float2::Extract(OvObject* pObj, OvObjectProperties& rObjStore)
{
	float* kpProp = (float*)Access(pObj);
	if (kpProp)
	{
		string kstrValue;
		float2_to_string(kpProp,kstrValue);
		rObjStore.PushValue(kstrValue);
		return true;
	}
	return false;
}
bool	OvProp_float2::Inject(OvObject* pObj, OvObjectProperties& rObjStore)
{
	float* kpProp = (float*)Access(pObj);
	if (kpProp)
	{
		string kstrValue;
		rObjStore.PopValue(kstrValue);
		string_to_float2(kstrValue,kpProp);
		return true;
	}
	return false;
}

////////////////////////////////////////////////////////////////////////////////////////////////
///////////////////////////				float3					/////////////////////////////
////////////////////////////////////////////////////////////////////////////////////////////////
#define float3_to_string(_float,_string) (_string = string(OvFormatString("%f %f %f",((_float)[0]),((_float)[1]),((_float)[2]))))
#define string_to_float3(_string,_float) (sscanf_s(_string.data(),"%f %f %f",&((_float)[0]),&((_float)[1]),&((_float)[2])))

OvRTTI_IMPL(OvProp_float3)
bool	OvProp_float3::Extract(OvObject* pObj, OvObjectProperties& rObjStore)
{
	float* kpProp = (float*)Access(pObj);
	if (kpProp)
	{
		string kstrValue;
		float3_to_string(kpProp,kstrValue);
		rObjStore.PushValue(kstrValue);
		return true;
	}
	return false;
}
bool	OvProp_float3::Inject(OvObject* pObj, OvObjectProperties& rObjStore)
{
	float* kpProp = (float*)Access(pObj);
	if (kpProp)
	{
		string kstrValue;
		rObjStore.PopValue(kstrValue);
		string_to_float3(kstrValue,kpProp);
		return true;
	}
	return false;
}

////////////////////////////////////////////////////////////////////////////////////////////////
///////////////////////////				float4					/////////////////////////////
////////////////////////////////////////////////////////////////////////////////////////////////
#define float4_to_string(_float,_string) (_string = string(OvFormatString("%f %f %f %f",((_float)[0]),((_float)[1]),((_float)[2]),((_float)[3]))))
#define string_to_float4(_string,_float) (sscanf_s(_string.data(),"%f %f %f %f",&((_float)[0]),&((_float)[1]),&((_float)[2]),&((_float)[3])))

OvRTTI_IMPL(OvProp_float4)
bool	OvProp_float4::Extract(OvObject* pObj, OvObjectProperties& rObjStore)
{
	float* kpProp = (float*)Access(pObj);
	if (kpProp)
	{
		string kstrValue;
		float4_to_string(kpProp,kstrValue);
		rObjStore.PushValue(kstrValue);
		return true;
	}
	return false;
}
bool	OvProp_float4::Inject(OvObject* pObj, OvObjectProperties& rObjStore)
{
	float* kpProp = (float*)Access(pObj);
	if (kpProp)
	{
		string kstrValue;
		rObjStore.PopValue(kstrValue);
		string_to_float4(kstrValue,kpProp);
		return true;
	}
	return false;
}

////////////////////////////////////////////////////////////////////////////////////////////////
///////////////////////////				transform					/////////////////////////////
////////////////////////////////////////////////////////////////////////////////////////////////

OvRTTI_IMPL(OvProp_transform)
bool	OvProp_transform::Extract(OvObject* pObj, OvObjectProperties& rObjStore)
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
bool	OvProp_transform::Inject(OvObject* pObj, OvObjectProperties& rObjStore)
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

OvRTTI_IMPL(OvProp_extra)
bool	OvProp_extra::Extract(OvObject* pObj, OvObjectProperties& rObjStore)
{
	
	OvObject::extra_property_table* kpProp = (OvObject::extra_property_table*)Access(pObj);

	if (kpProp)
	{
		OvObject::extra_property_table& extraTable = *kpProp;
		
		OliveValue::Integer extraCount;
		extraCount.SetInteger(extraTable.size());
		rObjStore.PushValue(extraCount.GetValue());

		for each( const OvObject::extra_property_table_pair extraProp in extraTable )
		{
			OliveValue::Value* extraValue = (OliveValue::Value*)extraProp.second;

			rObjStore.PushValue( OvRTTI_Util::TypeName( extraValue ) );
			rObjStore.PushValue( extraProp.first );
			rObjStore.PushValue( *extraValue );
		}

		return true;
	}
	return false;
}
bool	OvProp_extra::Inject(OvObject* pObj, OvObjectProperties& rObjStore)
{
	OvObject::extra_property_table* kpProp = (OvObject::extra_property_table*)Access(pObj);

	if (kpProp)
	{
		OvObject::extra_property_table& extraTable = *kpProp;

		OliveValue::Integer extraCount;
		rObjStore.PopValue(extraCount);
		for (int i = 0 ; i < extraCount.GetInteger() ; ++i)
		{
			string valueType;

			rObjStore.PopValue( valueType );
			OliveValue::Value*	extraValue = OliveValue::ValueFactory( valueType );
			if (extraValue)
			{
				string extraPropName;
				rObjStore.PopValue( extraPropName );
				rObjStore.PopValue( *extraValue );
				extraTable[ extraPropName ] = extraValue;
			}
		}
		return true;
	}
	return false;
}