#include "OvMessageManager.h"
#include "OvXObject.h"
#include "OliveValue.h"
#include "OvMessageListener.h"
#include "OvInputManager.h"
#include <algorithm>
using namespace std;

OvMessageManager::OvMessageManager()
: m_alive_flag( false )
{

}
OvMessageManager::~OvMessageManager()
{

}

OvBool	OvMessageManager::ListenMessage( HWND hWnd, UINT message, WPARAM wParam, LPARAM lParam)
{
	return GetInstance()->_listenMessage( hWnd, message, wParam, lParam );
}

OvBool	OvMessageManager::_listenMessage( HWND hWnd, UINT message, WPARAM wParam, LPARAM lParam)
{
	for each( OvMessageListener* listener in m_listenerList )
	{
		if ( listener && listener->GetTarget() )
		{
			listener->_push_message(OvMessageListener::InputMessage(hWnd,message,wParam,lParam));
		}
	}
	return true;
}
OvPoint2	OvMessageManager::GetLastMousePoint()
{
	return m_lastMousePoint;
}
OvPoint2	OvMessageManager::GetMouseInterval()
{
	return m_mouseMoveInterval;
}

void OvMessageManager::_register_listener( OvMessageListener* listener )
{
	if ( OvSTL_Find( m_listenerList, listener ) == m_listenerList.end() )
	{
		m_listenerList.push_back( listener );
	}
}

void OvMessageManager::_remove_listener( OvMessageListener* listener )
{
	listener_list::iterator itor = OvSTL_Find( m_listenerList, listener );
	if ( m_listenerList.end() != itor )
	{
		m_listenerList.erase( itor );
	}
}

void OvMessageManager::_update()
{
	MSG msg;
	ZeroMemory( &msg, sizeof( msg ) );
	if ( PeekMessage( &msg, NULL, NULL, NULL, PM_REMOVE ) )
	{
		TranslateMessage( &msg );
		DispatchMessage( &msg );
		m_alive_flag = (msg.message != WM_QUIT);
	}
}

OvBool OvMessageManager::IsWindowAlive()
{
	return m_alive_flag;
}