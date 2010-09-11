#pragma once
#include "OvPropertyAccesser.h"

// bool Property
class OvPropAccesser_bool : public OvPropertyAccesser
{
	OvRTTI_DECL(OvPropAccesser_bool);
	virtual bool	Extract(OvObject* pObj, OvObjectProperties& rObjStore);
	virtual bool	Inject(OvObject* pObj, OvObjectProperties& rObjStore);
};
//


// integer Property
class OvPropAccesser_integer : public OvPropertyAccesser
{
	OvRTTI_DECL(OvPropAccesser_integer);
	virtual bool	Extract(OvObject* pObj, OvObjectProperties& rObjStore);
	virtual bool	Inject(OvObject* pObj, OvObjectProperties& rObjStore);
};
//

// stl::string Property
class OvPropAccesser_STL_string : public OvPropertyAccesser
{
	OvRTTI_DECL(OvPropAccesser_STL_string);
	virtual bool	Extract(OvObject* pObj, OvObjectProperties& rObjStore);
	virtual bool	Inject(OvObject* pObj, OvObjectProperties& rObjStore);
};
//

// object_pointer Property
class OvPropAccesser_object_pointer : public OvPropertyAccesser
{
	OvRTTI_DECL(OvPropAccesser_object_pointer);
	virtual bool	Extract(OvObject* pObj, OvObjectProperties& rObjStore);
	virtual bool	Inject(OvObject* pObj, OvObjectProperties& rObjStore);
};
//

// OvPropAccesser_object_smart_pointer Property
class OvPropAccesser_object_smart_pointer : public OvPropertyAccesser
{
	OvRTTI_DECL(OvPropAccesser_object_smart_pointer);
	virtual bool	Extract(OvObject* pObj, OvObjectProperties& rObjStore);
	virtual bool	Inject(OvObject* pObj, OvObjectProperties& rObjStore);
};
//

// float Property
class OvPropAccesser_float : public OvPropertyAccesser
{
	OvRTTI_DECL(OvPropAccesser_float);
	virtual bool	Extract(OvObject* pObj, OvObjectProperties& rObjStore);
	virtual bool	Inject(OvObject* pObj, OvObjectProperties& rObjStore);
};
//

// float3 Property
class OvPropAccesser_float2 : public OvPropertyAccesser
{
	OvRTTI_DECL(OvPropAccesser_float2);
	virtual bool	Extract(OvObject* pObj, OvObjectProperties& rObjStore);
	virtual bool	Inject(OvObject* pObj, OvObjectProperties& rObjStore);
};

// float3 Property
class OvPropAccesser_float3 : public OvPropertyAccesser
{
	OvRTTI_DECL(OvPropAccesser_float3);
	virtual bool	Extract(OvObject* pObj, OvObjectProperties& rObjStore);
	virtual bool	Inject(OvObject* pObj, OvObjectProperties& rObjStore);
};
//

// float4 Property
class OvPropAccesser_float4 : public OvPropertyAccesser
{
	OvRTTI_DECL(OvPropAccesser_float4);
	virtual bool	Extract(OvObject* pObj, OvObjectProperties& rObjStore);
	virtual bool	Inject(OvObject* pObj, OvObjectProperties& rObjStore);
};
//

// transform Property
class OvPropAccesser_transform : public OvPropertyAccesser
{
	OvRTTI_DECL(OvPropAccesser_transform);
	virtual bool	Extract(OvObject* pObj, OvObjectProperties& rObjStore);
	virtual bool	Inject(OvObject* pObj, OvObjectProperties& rObjStore);
};
//

// extra Property
class OvPropAccesser_extra_data : public OvPropertyAccesser
{
	OvRTTI_DECL(OvPropAccesser_extra_data);
	virtual bool	Extract(OvObject* pObj, OvObjectProperties& rObjStore);
	virtual bool	Inject(OvObject* pObj, OvObjectProperties& rObjStore);
};
//

// objectcollector Property
class OvPropAccesser_object_collector : public OvPropertyAccesser
{
	OvRTTI_DECL(OvPropAccesser_object_collector);
	virtual bool	Extract(OvObject* pObj, OvObjectProperties& rObjStore);
	virtual bool	Inject(OvObject* pObj, OvObjectProperties& rObjStore);
};
//

//resource Property
class OvResourceLoader;
class OvPropAccesser_resource : public OvPropertyAccesser
{
	OvRTTI_DECL(OvPropAccesser_resource);
	virtual bool	Extract(OvObject* pObj, OvObjectProperties& rObjStore);
	virtual bool	Inject(OvObject* pObj, OvObjectProperties& rObjStore);
};