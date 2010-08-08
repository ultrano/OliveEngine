#pragma once
#include "OvRefBase.h"
class OvStoreObject;
class OvPoint3;
OvREF_POINTER(OvObject);

namespace OvStoreUtility
{

#define STORE_TYPE_INTEGER		("interger")
	bool WriteInteger(OvStoreObject*,const int&);
	bool ReadInteger(OvStoreObject*,int&);

#define STORE_TYPE_FLOAT		("float")
	bool WriteFloat(OvStoreObject*,const float&);
	bool ReadFloat(OvStoreObject*,float&);

#define STORE_TYPE_DOUBLE		("double")
	bool WriteDouble(OvStoreObject*,const double&);
	bool ReadFDouble(OvStoreObject*,double&);

#define STORE_TYPE_POINT3		("point3")
	bool WritePoint3(OvStoreObject*,const OvPoint3&);
	bool ReadPoint3(OvStoreObject*,OvPoint3&);

}
namespace OSU = OvStoreUtility;