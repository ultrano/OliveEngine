#pragma once
#include "OvSingleton.h"
#include "OvResource.h"
#include "OvResourceLoader.h"
#include "OvResourceTicket.h"
#include <string>
#include <list>
#include <map>

//! 모든 리소스는 resource폴더 밑에 위치하는것으로 간주 한다.(다른 디스크, 외부폴더로의 리소스 유입은 금지한다.)
//! 리소스 관리를 위한 단계이다.
class OvResourceManager : public OvSingletonBase< OvResourceManager >
{
	friend class OvResource;
	friend class OvResourceTicket;

public:

	OvResourceManager();
	~OvResourceManager();

	//! sync load method
	template<typename Type_0>
	OvSmartPointer<Type_0>	LoadResource( const string& fileLocation );
	OvResourceSPtr			LoadResource( const OvRTTI* resourceType, const string& fileLocation );
	OvResourceSPtr			LoadResource( const string& resourceType, const string& fileLocation );
	//

	//! async load method
	OvResourceTicketSPtr	AsyncLoadResource( const OvRTTI* resourceType, const string& fileLocation );
	OvResourceTicketSPtr	AsyncLoadResource( const string& resourceType, const string& fileLocation );

	OvResourceTicketSPtr	FindTicket( OvResourceSPtr resource );
	//


	void					ResourceCache( OvResourceSPtr resource );
	const string&			FindFileLocation( OvResourceSPtr resource );

	const string&			ResourceDirectory();

private:

	struct SAsyncLoadInfo
	{ 
		std::string file; 
		OvResourceLoaderSPtr loader; 
	};
	struct SResourceInfo
	{
		SResourceInfo():resource(NULL),ticket(NULL){};
		OvResource* resource;
		OvResourceTicket* ticket;
	};
	typedef std::map<const OvRTTI*, OvResourceLoaderSPtr>	resource_loader_table;
	typedef std::list< OvResourceSPtr >						resource_cache_list;
	typedef std::list< SAsyncLoadInfo >						async_load_list;

	typedef std::map< std::string, SResourceInfo >			loaded_resource_table;
	typedef std::list< OvResource* >						resource_list;
private:

	OvResourceTicketSPtr	_reserve_ticket( const OvRTTI* type, const string& fileLocation );
	void _register_loaded_resource( const string& location, OvResource* resource );

	OvResourceLoaderSPtr _find_resource_loader( const OvRTTI* resourceType );
	OvResourceSPtr _find_loaded_resource( const OvRTTI* resourceType, const string& location);

	void	_called_when_resource_created( OvResource* resource );
	void	_called_when_resource_deleted( OvResource* resource );

	void	_called_when_ticket_created( OvResourceTicket* ticket );
	void	_called_when_ticket_deleted( OvResourceTicket* ticket );

	static	void	_thread_routine( void* data );
	static bool&	_get_async_life_flag();
	void	_async_routine();

	void	_push_async_load_info( SAsyncLoadInfo& info );
	bool	_pop_async_load_info( SAsyncLoadInfo& info );

private:
	resource_list			m_resourceList;
	loaded_resource_table	m_resourceInfoTable;
	resource_loader_table	m_loaderTable;
	resource_cache_list		m_cacheList;

	async_load_list			m_aload_list;
	CRITICAL_SECTION		m_load_section;
	CRITICAL_SECTION		m_life_section;
	HANDLE					m_async_handle;

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