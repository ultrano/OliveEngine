#pragma once
#include "OvSingleton.h"
#include "OvResource.h"
#include <string>
#include <list>
#include <map>

class OvResourceManager : public OvSingletonBase< OvResourceManager >
{
	typedef std::map<const OvRTTI*, OvResourceLoaderSPtr>	resource_loader_table;
	typedef std::map< OvResource*, std::string >			resource_table;
	typedef std::list< OvResourceSPtr >						resource_cache_list;
	friend class OvResource;
public:
	OvResourceManager();
	~OvResourceManager();

	template<typename Type_0>
	OvSmartPointer<Type_0>	LoadResource( const string& fileLocation );
	OvResourceSPtr	LoadResource( const OvRTTI* resourceType, const string& fileLocation );
	OvResourceSPtr	LoadResource( const string& resourceType, const string& fileLocation );

	void			ResourceCache( OvResourceSPtr resource );

	string			FindFileLocation( OvResource* resource );

private:

	void _register_loaded_resource( OvResource* resource, const string& location );
	void	_resource_created( OvResource* resource );
	void	_resource_deleted( OvResource* resource );
	OvResourceSPtr _find_loaded_resource( const OvRTTI* resourceType, const string& location);
private:
	resource_loader_table	m_loaderTable;
	resource_table	m_resourceTable;
	resource_cache_list m_cacheList;
};

template<typename Type_0>
OvSmartPointer<Type_0> 
OvResourceManager::LoadResource( const string& fileLocation )
{
	return LoadResource( Type_0::GetRTTI(), fileLocation );
};