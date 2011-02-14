#include "OvTask.h"
#include "OvTaskManager.h"

OvTask::OvTask( const OvString& name )
: m_name( name )
{
	OvTaskManager::GetInstance()->_add_task( this );
}
OvTask::~OvTask()
{
	OvTaskManager::GetInstance()->_remove_task( this );
}