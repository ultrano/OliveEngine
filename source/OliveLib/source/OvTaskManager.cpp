#include "OvTaskManager.h"
#include "OvUtility.h"

void OvTaskManager::_add_task( OvTask * task )
{
	OvAutoSection lock( m_cs );
	m_tasks.push_back( task );
}

void OvTaskManager::_remove_task( OvTask * task )
{
	OvAutoSection lock( m_cs );
	OU::container::remove( m_tasks, task );
}