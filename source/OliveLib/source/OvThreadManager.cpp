#include "OvThreadManager.h"
#include "OvUtility.h"

void OvThreadManager::_add_thread( OvThread * task )
{
	OvAutoSection lock( m_cs );
	m_threads.push_back( task );
}

void OvThreadManager::_remove_thread( OvThread * task )
{
	OvAutoSection lock( m_cs );
	OU::container::remove( m_threads, task );
}