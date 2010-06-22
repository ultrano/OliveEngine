#pragma once
#include "OvRefBase.h"
#include "OvBitFlags.h"

OvREF_POINTER(OvResource);
class OvResource : public OvRefBase
{
	OvRTTI_DECL(OvResource);
public:
	OvResource();
	~OvResource();
	
	virtual bool	Load( const std::string& fileLocation ) = 0;

	bool	IsLoadingCompleted();
	bool	IsAsyncLoading();
	void	SetAsyncLoading(bool asyncLoad);

private:
	bool	_resource_load( const std::string& fileLocation );
	void	_set_loading_completed( bool loadCompleted );
private:
	Ov8SetFlags	m_resSetting;
	CRITICAL_SECTION	m_criticalSection;
};