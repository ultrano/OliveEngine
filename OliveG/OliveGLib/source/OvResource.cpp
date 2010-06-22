#include "OvResource.h"

OvRTTI_IMPL(OvResource);

enum resource_setting_flags
{
	is_loading_completed,
	is_async_loading
};

struct SSectionGuardian
{
	SSectionGuardian(CRITICAL_SECTION& section):m_targetSection(section)
	{
		EnterCriticalSection( & m_targetSection );
	};
	~SSectionGuardian()
	{
		DeleteCriticalSection( & m_targetSection );
	};
	CRITICAL_SECTION& m_targetSection;
};

OvResource::OvResource()
{
	InitializeCriticalSection( & m_criticalSection );

	m_resSetting.SetFlag( is_async_loading, false );
	m_resSetting.SetFlag( is_loading_completed, false );

}

OvResource::~OvResource()
{
	DeleteCriticalSection( & m_criticalSection );
}

bool	OvResource::_resource_load( const std::string& fileLocation )
{
	bool loadSuccess = Load( fileLocation );
	_set_loading_completed( loadSuccess );
	return loadSuccess;
}

void	OvResource::_set_loading_completed( bool loadCompleted )
{
	SSectionGuardian sectionGuardian( m_criticalSection );
	m_resSetting.SetFlag( is_loading_completed, loadCompleted );
}

bool	OvResource::IsLoadingCompleted()
{
	SSectionGuardian sectionGuardian( m_criticalSection );
	return m_resSetting.GetFlag( is_loading_completed );
}

bool	OvResource::IsAsyncLoading()
{
	return m_resSetting.GetFlag( is_async_loading );
}

void	OvResource::SetAsyncLoading(bool asyncLoad)
{
	m_resSetting.SetFlag( is_async_loading, asyncLoad );
}