#include "OvMessageManager.h"
#include "OvXObject.h"
#include "OliveValue.h"
#include "OvMessageListener.h"
#include <algorithm>
using namespace std;

OvWinMsgManager::OvWinMsgManager()
{

}
OvWinMsgManager::~OvWinMsgManager()
{

}

bool	OvWinMsgManager::ListenMessage( HWND hWnd, UINT message, WPARAM wParam, LPARAM lParam)
{
	return GetInstance()->_listenMessage( hWnd, message, wParam, lParam );
}

bool	OvWinMsgManager::_listenMessage( HWND hWnd, UINT message, WPARAM wParam, LPARAM lParam)
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
OvPoint2	OvWinMsgManager::GetLastMousePoint()
{
	return m_lastMousePoint;
}
OvPoint2	OvWinMsgManager::GetMouseInterval()
{
	return m_mouseMoveInterval;
}

void OvWinMsgManager::_register_listener( OvMessageListener* listener )
{
	if ( OvSTL_Find( m_listenerList, listener ) == m_listenerList.end() )
	{
		m_listenerList.push_back( listener );
	}
}

void OvWinMsgManager::_remove_listener( OvMessageListener* listener )
{
	listener_list::iterator itor = OvSTL_Find( m_listenerList, listener );
	if ( m_listenerList.end() != itor )
	{
		m_listenerList.erase( itor );
	}
}