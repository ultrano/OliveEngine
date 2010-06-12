#include "OvStoreUtility.h"
#include "OvStringUtility.h"
#include "OvStoreData.h"
#include "OvPoint3.h"
#include "OvObject.h"
#include <boost/lexical_cast.hpp>

using namespace boost;
using namespace OvStoreUtility;


bool OSU::WriteInteger(OvStoreObject* pObj,const int& rInput)
{
	if (OvRTTI_Util::IsTypeOf< OvStoreData >( pObj ) )
	{
		try
		{
			OvStoreData* kpData = (OvStoreData*)pObj;
			kpData->SetDataType(STORE_TYPE_INTEGER);
			kpData->SetDataString(lexical_cast<string>(rInput).data());
			return true;
		}
		catch (bad_lexical_cast& e)
		{
			OvAssertMsg(e.what());
			return false;
		}
	}
	return false;
}
bool OSU::ReadInteger(OvStoreObject* pObj,int& rOutput)
{
	if (OvRTTI_Util::IsTypeOf< OvStoreData >( pObj ) )
	{
		try
		{
			OvStoreData* kpData = (OvStoreData*)pObj;
			if (string(STORE_TYPE_INTEGER) == kpData->GetDataType())
			{
				string kstrData = kpData->GetDataString();
				rOutput = lexical_cast<int>(kstrData);
				return true;
			}
		}
		catch (bad_lexical_cast& e)
		{
			OvAssertMsg(e.what());
			return false;
		}
	}
	return false;
}
bool OSU::WriteFloat(OvStoreObject* pObj,const float& rInput)
{
	if (OvRTTI_Util::IsTypeOf< OvStoreData >( pObj ) )
	{
		try
		{
			OvStoreData* kpData = (OvStoreData*)pObj;
			kpData->SetDataType(STORE_TYPE_FLOAT);
			kpData->SetDataString(lexical_cast<string>(rInput).data());
			return true;
		}
		catch (bad_lexical_cast& e)
		{
			OvAssertMsg(e.what());
			return false;
		}
	}
	return false;
}
bool OSU::ReadFloat(OvStoreObject* pObj,float& rOutput)
{
	if (OvRTTI_Util::IsTypeOf< OvStoreData >( pObj ) )
	{
		try
		{
			OvStoreData* kpData = (OvStoreData*)pObj;
			if (string(STORE_TYPE_FLOAT) == kpData->GetDataType())
			{
				string kstrData = kpData->GetDataString();
				rOutput = lexical_cast<float>(kstrData);
				return true;
			}
		}
		catch (bad_lexical_cast& e)
		{
			OvAssertMsg(e.what());
			return false;
		}
	}
	return false;
}

bool OSU::WriteDouble(OvStoreObject* pObj,const double& rData)
{
	if ( OvRTTI_Util::IsTypeOf< OvStoreData >( pObj ) )
	{
		try
		{
			OvStoreData* kpData = (OvStoreData*)pObj;
			kpData->SetDataType(STORE_TYPE_DOUBLE);
			kpData->SetDataString(lexical_cast<string>(rData).data());
			return true;
		}
		catch (bad_lexical_cast& e)
		{
			OvAssertMsg(e.what());
			return false;
		}
	}
	return false;
}
bool OSU::ReadFDouble(OvStoreObject* pObj,double& rData)
{
	if ( OvRTTI_Util::IsTypeOf< OvStoreData >( pObj ) )
	{
		try
		{
			OvStoreData* kpData = (OvStoreData*)pObj;
			if (string(STORE_TYPE_DOUBLE) == kpData->GetDataType())
			{
				string kstrData = kpData->GetDataString();
				rData = lexical_cast<double>(kstrData);
				return true;
			}
		}
		catch (bad_lexical_cast& e)
		{
			OvAssertMsg(e.what());
			return false;
		}
	}
	return false;
}
bool OSU::WritePoint3(OvStoreObject* pObj,const OvPoint3& rInput)
{
	if ( OvRTTI_Util::IsTypeOf< OvStoreData >( pObj ) )
	{
		OvStoreData* kpData = (OvStoreData*)pObj;
		kpData->SetDataType(STORE_TYPE_POINT3);
		kpData->SetDataString(OvFormatString("%f,%f,%f",rInput.x,rInput.y,rInput.z));
		return true;
	}
	return false;
}
bool OSU::ReadPoint3(OvStoreObject* pObj,OvPoint3& rOutput)
{
	if ( OvRTTI_Util::IsTypeOf< OvStoreData >( pObj ) )
	{
		OvStoreData* kpData = (OvStoreData*)pObj;
		sscanf_s(kpData->GetDataString(),"%f,%f,%f",&rOutput.x,&rOutput.y,&rOutput.z);
		return true;
	}
	return false;
}

