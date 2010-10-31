#include "OvMessageManager.h"
#include "OvXObject.h"
#include "OliveValue.h"
#include "OvMessageListener.h"
#include "OvInputManager.h"
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
	switch ( message )
	{
	case WM_NCLBUTTONDOWN : 
	case WM_LBUTTONDOWN : 
		OvInputManager::GetInstance()->_notify_mouse_state( L_BUTTON, PRESSED );
		break;
	case WM_NCMBUTTONDOWN : 
	case WM_MBUTTONDOWN : 
		OvInputManager::GetInstance()->_notify_mouse_state( M_BUTTON, PRESSED );
		break;
	case WM_NCRBUTTONDOWN : 
	case WM_RBUTTONDOWN : 
		OvInputManager::GetInstance()->_notify_mouse_state( R_BUTTON, PRESSED );
		break;

	case WM_NCLBUTTONUP : 
	case WM_LBUTTONUP : 
		OvInputManager::GetInstance()->_notify_mouse_state( L_BUTTON, RELEASED );
		break;
	case WM_NCMBUTTONUP : 
	case WM_MBUTTONUP : 
		OvInputManager::GetInstance()->_notify_mouse_state( M_BUTTON, RELEASED );
		break;
	case WM_NCRBUTTONUP : 
	case WM_RBUTTONUP : 
		OvInputManager::GetInstance()->_notify_mouse_state( R_BUTTON, RELEASED );
		break;

	case WM_NCLBUTTONDBLCLK : 
	case WM_LBUTTONDBLCLK : 
		OvInputManager::GetInstance()->_notify_mouse_state( L_BUTTON, DBCLICKED );
		break;
	case WM_NCMBUTTONDBLCLK : 
	case WM_MBUTTONDBLCLK : 
		OvInputManager::GetInstance()->_notify_mouse_state( M_BUTTON, DBCLICKED );
		break;
	case WM_NCRBUTTONDBLCLK : 
	case WM_RBUTTONDBLCLK : 
		OvInputManager::GetInstance()->_notify_mouse_state( R_BUTTON, DBCLICKED );

	default:
		OvInputManager::GetInstance()->_clear_click_state();
		break;
	}

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