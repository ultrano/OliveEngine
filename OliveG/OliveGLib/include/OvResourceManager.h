#pragma once
#include "OvSingleton.h"
#include "OvResource.h"
#include <string>
#include <map>

class OvResourceManager : public OvSingletonBase< OvResourceManager >
{
	typedef std::map<const OvRTTI*, OvResourceLoaderSPtr> resource_loader_table;
	typedef std::map<const std::string, OvResource* >	resource_table;
	friend class OvResource;
public:
	OvResourceManager();
	~OvResourceManager();

	OvResourceSPtr	LoadResource( const OvRTTI* resourceType, const string& fileLocation );
	OvResourceSPtr	LoadResource( const string& resourceType, const string& fileLocation );


	template<typename Type_0>
	OvSmartPointer<Type_0>	LoadResource( const string& fileLocation )
	{
		return LoadResource( Type_0::GetRTTI(), fileLocation );
	};

private:

	void	_register_resource(const string& location, OvResource* resource);
	void	_resource_deleted( OvResource* resource );
	OvResourceSPtr	_find_loaded_resource(const string& location);
private:
	resource_loader_table	m_loaderTable;
	resource_table	m_resourceTable;
};