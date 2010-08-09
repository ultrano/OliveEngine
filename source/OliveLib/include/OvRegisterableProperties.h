#pragma once
#include "OvProperty.h"

enum eRegisterable_Prop
{
	Prop_bool,
	Prop_integer,
	Prop_STL_string,
	Prop_float,
	Prop_float2,
	Prop_float3,
	Prop_float4,
	Prop_transform,

};

// bool Property
class OvProp_bool : public OvProperty
{
	OvRTTI_DECL(OvProp_bool);
	virtual bool	Extract(OvObject* pObj, OvObjectProperties& rObjStore);
	virtual bool	Inject(OvObject* pObj, OvObjectProperties& rObjStore);
};
//


// integer Property
class OvProp_integer : public OvProperty
{
	OvRTTI_DECL(OvProp_integer);
	virtual bool	Extract(OvObject* pObj, OvObjectProperties& rObjStore);
	virtual bool	Inject(OvObject* pObj, OvObjectProperties& rObjStore);
};
//

// stl::string Property
class OvProp_STL_string : public OvProperty
{
	OvRTTI_DECL(OvProp_STL_string);
	virtual bool	Extract(OvObject* pObj, OvObjectProperties& rObjStore);
	virtual bool	Inject(OvObject* pObj, OvObjectProperties& rObjStore);
};
//

// object_pointer Property
class OvProp_object_pointer : public OvProperty
{
	OvRTTI_DECL(OvProp_object_pointer);
	virtual bool	Extract(OvObject* pObj, OvObjectProperties& rObjStore);
	virtual bool	Inject(OvObject* pObj, OvObjectProperties& rObjStore);
};
//

// OvProp_object_smart_pointer Property
class OvProp_object_smart_pointer : public OvProperty
{
	OvRTTI_DECL(OvProp_object_smart_pointer);
	virtual bool	Extract(OvObject* pObj, OvObjectProperties& rObjStore);
	virtual bool	Inject(OvObject* pObj, OvObjectProperties& rObjStore);
};
//

// float Property
class OvProp_float : public OvProperty
{
	OvRTTI_DECL(OvProp_float);
	virtual bool	Extract(OvObject* pObj, OvObjectProperties& rObjStore);
	virtual bool	Inject(OvObject* pObj, OvObjectProperties& rObjStore);
};
//

// float3 Property
class OvProp_float2 : public OvProperty
{
	OvRTTI_DECL(OvProp_float2);
	virtual bool	Extract(OvObject* pObj, OvObjectProperties& rObjStore);
	virtual bool	Inject(OvObject* pObj, OvObjectProperties& rObjStore);
};

// float3 Property
class OvProp_float3 : public OvProperty
{
	OvRTTI_DECL(OvProp_float3);
	virtual bool	Extract(OvObject* pObj, OvObjectProperties& rObjStore);
	virtual bool	Inject(OvObject* pObj, OvObjectProperties& rObjStore);
};
//

// float4 Property
class OvProp_float4 : public OvProperty
{
	OvRTTI_DECL(OvProp_float4);
	virtual bool	Extract(OvObject* pObj, OvObjectProperties& rObjStore);
	virtual bool	Inject(OvObject* pObj, OvObjectProperties& rObjStore);
};
//

// transform Property
class OvProp_transform : public OvProperty
{
	OvRTTI_DECL(OvProp_transform);
	virtual bool	Extract(OvObject* pObj, OvObjectProperties& rObjStore);
	virtual bool	Inject(OvObject* pObj, OvObjectProperties& rObjStore);
};
//

// extra Property
class OvProp_extra : public OvProperty
{
	OvRTTI_DECL(OvProp_extra);
	virtual bool	Extract(OvObject* pObj, OvObjectProperties& rObjStore);
	virtual bool	Inject(OvObject* pObj, OvObjectProperties& rObjStore);
};
//

// objectcollector Property
class OvProp_object_collector : public OvProperty
{
	OvRTTI_DECL(OvProp_object_collector);
	virtual bool	Extract(OvObject* pObj, OvObjectProperties& rObjStore);
	virtual bool	Inject(OvObject* pObj, OvObjectProperties& rObjStore);
};
//

//resource Property
class OvResourceLoader;
class OvProp_resource : public OvProperty
{
	OvRTTI_DECL(OvProp_resource);
	virtual bool	Extract(OvObject* pObj, OvObjectProperties& rObjStore);
	virtual bool	Inject(OvObject* pObj, OvObjectProperties& rObjStore);
};