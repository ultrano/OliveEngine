#pragma once
#include "OvValueStream.h"
#include "OvRefBase.h"
#include "OvStorage.h"
#include "OvSingleton.h"
#include <map>
OvREF_POINTER(OvObject);
class OvObjectFactory : public OvMemObject
{
	OvSingletonEx_DECL(OvObjectFactory);
public:

	typedef OvObjectSPtr (*OvManufactureFunctor)(OvStorage&);

	static OvObjectSPtr	RuntimeManufacture(const char* pClassName,OvStorage& cStorage);

	template<typename Class_0>
	static OvObjectSPtr	TemplateManufactureFunctor(OvStorage& cConstructDesc);

	template<typename Class_0>
	static void			RegisterClassManufacture(const char* pClassName);

private:

	map<string,OvManufactureFunctor>	m_mapManufactures;

};

#include "OvObjectFactory.inl"

#define OvREGISTERRUNTIMECLASS(__class_name)	OvObjectFactory::RegisterClassManufacture<__class_name>(#__class_name);