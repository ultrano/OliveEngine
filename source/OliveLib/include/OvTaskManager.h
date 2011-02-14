#pragma once
#include "OvSingleton.h"
#include "OvTypeDef.h"
#include "OvThreadSync.h"

class OvTask;
class OvTaskManager : public OvSingletonBase< OvTaskManager >
{
	friend class OvTask;

public:

private:

	void	_add_task( OvTask * task );
	void	_remove_task( OvTask * task );

private:

	OvList< OvTask * > m_tasks;
	OvCriticalSection  m_cs;

};