#include "OvInputDevice.h"
#include "OvXObject.h"
#include "OliveValue.h"
#include "OvInputEventListener.h"
#include <algorithm>
using namespace std;

OvInputDevice::OvInputDevice()
{

}
OvInputDevice::~OvInputDevice()
{

}

bool	OvInputDevice::ListenMessage( HWND hWnd, UINT message, WPARAM wParam, LPARAM lParam)
{
	return GetInstance()->_listenMessage( hWnd, message, wParam, lParam );
}

bool	OvInputDevice::_listenMessage( HWND hWnd, UINT message, WPARAM wParam, LPARAM lParam)
{
	switch ( message )
	{
	case WM_MOUSEMOVE : 

		OvPoint2 mousePoint;
		mousePoint.x = ( float )LOWORD( lParam );
		mousePoint.y = ( float )HIWORD( lParam );
		m_mouseMoveInterval = mousePoint - m_lastMousePoint;
		m_lastMousePoint = mousePoint;
		break;
	}

	for each( OvInputEventListener* listener in m_listenerList )
	{
		if ( listener && listener->GetTarget() )
		{
			listener->_push_message(OvInputEventListener::InputMessage(hWnd,message,wParam,lParam));
		}
	}
	return true;
}
OvPoint2	OvInputDevice::GetLastMousePoint()
{
	return m_lastMousePoint;
}
OvPoint2	OvInputDevice::GetMouseInterval()
{
	return m_mouseMoveInterval;
}

void OvInputDevice::_register_listener( OvInputEventListener* listener )
{
	if ( OvSTL_Find( m_listenerList, listener ) == m_listenerList.end() )
	{
		m_listenerList.push_back( listener );
	}
}

void OvInputDevice::_remove_listener( OvInputEventListener* listener )
{
	listener_list::iterator itor = OvSTL_Find( m_listenerList, listener );
	if ( m_listenerList.end() != itor )
	{
		m_listenerList.erase( itor );
	}
}