#include "OvThread.h"
#include "OvThreadManager.h"
#include <process.h>

OvThread::OvThread( const OvString& name )
: m_thread( NULL )
, m_func( NULL )
{
	OvThreadManager::GetInstance()->_add_thread( this );
}

OvThread::OvThread( const OvString& name, FuncType func )
: m_thread( NULL )
, m_func( func )
{
	OvThreadManager::GetInstance()->_add_thread( this );
}

OvThread::~OvThread()
{
	OvThreadManager::GetInstance()->_remove_thread( this );
	TerminateThread( m_thread, -1 );
	CloseHandle( m_thread );
}

void OvThread::Start()
{
	m_thread = (HANDLE)_beginthread( m_func, NULL, NULL );
}

void OvThread::Suspend()
{
	SuspendThread( m_thread );
}

void OvThread::Resume()
{
	ResumeThread( m_thread );
}

void OvThread::Run()
{

}