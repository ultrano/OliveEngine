#pragma once
#include "OvSingleton.h"
#include "OvResource.h"
#include <string>
#include <list>
#include <map>

//! 모든 리소스는 resource폴더 밑에 위치하는것으로 간주 한다.(다른 디스크, 외부폴더로의 리소스 유입은 금지한다.)
//! 리소스 관리를 위한 단계이다.
class OvResourceManager : public OvSingletonBase< OvResourceManager >
{
	typedef std::map<const OvRTTI*, OvResourceLoaderSPtr>	resource_loader_table;
	typedef std::map< OvResource*, std::string >			resource_location_table;
	typedef std::map< std::string, OvResourceTicket* >		resource_ticket_table;
	typedef std::list< OvResourceSPtr >						resource_cache_list;	
	friend class OvResource;
	friend class OvResourceTicket;
public:
	OvResourceManager();
	~OvResourceManager();

	template<typename Type_0>
	OvSmartPointer<Type_0>	LoadResource( const string& fileLocation );
	OvResourceSPtr	LoadResource( const OvRTTI* resourceType, const string& fileLocation );
	OvResourceSPtr	LoadResource( const string& resourceType, const string& fileLocation );

	OvResourceSPtr	ReloadResource( const string& fileLocation );
	OvResourceSPtr	ReloadResource( OvResourceSPtr resource );
	void			ReloadResourceAll();

	void			ResourceCache( OvResourceSPtr resource );

	string			FindFileLocation( OvResourceSPtr resource );

	OvResourceTicketSPtr	CheckIn(  OvResourceSPtr resource );

	const string&	ResourceDirectory();

private:

	void _register_loaded_resource( OvResource* resource, const string& location );
	OvResourceSPtr _find_loaded_resource( const OvRTTI* resourceType, const string& location);
	void	_called_when_resource_created( OvResource* resource );
	void	_called_when_resource_deleted( OvResource* resource );
	void	_called_when_ticket_created( OvResourceTicket* ticket );
	void	_called_when_ticket_deleted( OvResourceTicket* ticket );
	OvResourceSPtr _force_load_resouroce( const OvRTTI* resourceType, const string& fileLocation );

private:
	resource_loader_table	m_loaderTable;
	resource_location_table	m_resourceLocationTable;
	resource_cache_list		m_cacheList;
	resource_ticket_table	m_resourceTicketTable;
	std::string				m_resourceDirectory;
};

template<typename Type_0>
OvSmartPointer<Type_0> 
OvResourceManager::LoadResource( const string& fileLocation )
{
	return LoadResource( Type_0::GetRTTI(), fileLocation );
};

string	ResDirPath( const std::string& file );
bool	ClampPathIfResDir( std::string& file );