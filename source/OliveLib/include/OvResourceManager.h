#pragma once
#include "OvSingleton.h"
#include "OvResource.h"
#include "OvResourceLoader.h"
#include "OvResourceTicket.h"
#include <string>
#include <list>
#include <map>

//! ��� ���ҽ��� resource���� �ؿ� ��ġ�ϴ°����� ���� �Ѵ�.(�ٸ� ��ũ, �ܺ��������� ���ҽ� ������ �����Ѵ�.)
//! ���ҽ� ������ ���� �ܰ��̴�.
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
	string					FindFileLocation( OvResourceSPtr resource );

	const string&			ResourceDirectory();

private:

	struct SAsyncLoadInfo
	{ 
		std::string file; 
		OvResourceLoaderSPtr loader; 
	};
	typedef std::map<const OvRTTI*, OvResourceLoaderSPtr>	resource_loader_table;
	typedef std::map< OvResource*, std::string >			resource_location_table;
	typedef std::map< std::string, OvResourceTicket* >		resource_ticket_table;
	typedef std::list< OvResourceSPtr >						resource_cache_list;
	typedef std::list< SAsyncLoadInfo >						async_load_list;

private:

	void _register_loaded_resource( OvResource* resource, const string& location );

	void _set_resource_location( OvResource* resource, const string& location );
	OvResourceLoaderSPtr _find_resource_loader( const OvRTTI* resourceType );
	OvResourceSPtr _find_loaded_resource( const OvRTTI* resourceType, const string& location);

	void	_called_when_resource_created( OvResource* resource );
	void	_called_when_resource_deleted( OvResource* resource );

	void	_called_when_ticket_created( OvResourceTicket* ticket );
	void	_called_when_ticket_deleted( OvResourceTicket* ticket );

	OvResourceSPtr _force_load_resouroce( const OvRTTI* resourceType, const string& fileLocation );

	static	void	_thread_routine( void* data );
	static bool&	_get_async_life_flag();
	void	_async_routine();

	OvResourceTicketSPtr	_check_ticket( const OvRTTI* type, const string& fileLocation );
	void	_push_async_load_info( SAsyncLoadInfo& info );
	bool	_pop_async_load_info( SAsyncLoadInfo& info );

private:
	resource_loader_table	m_loaderTable;
	resource_location_table	m_resourceLocationTable;
	resource_cache_list		m_cacheList;
	resource_ticket_table	m_resourceTicketTable;

	async_load_list			m_aload_list;
	CRITICAL_SECTION		m_load_section;
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