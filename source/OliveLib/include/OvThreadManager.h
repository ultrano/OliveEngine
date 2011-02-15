#pragma once
#include "OvSingleton.h"
#include "OvTypeDef.h"
#include "OvThreadSync.h"

class OvThread;
class OvThreadManager : public OvSingletonBase< OvThreadManager >
{
	friend class OvThread;

public:

private:

	void	_add_thread( OvThread * task );
	void	_remove_thread( OvThread * task );

private:

	OvList< OvThread * > m_threads;
	OvCriticalSection  m_cs;

};