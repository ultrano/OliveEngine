#include "OvInputDevice.h"
#include "OliveValue.h"

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
		mousePoint.x = ( float )HIWORD( lParam );
		mousePoint.y = ( float )LOWORD( lParam );
		m_mouseMoveInterval = mousePoint - m_lastMousePoint;
		m_lastMousePoint = mousePoint;
		OliveValue::Point2 test(m_mouseMoveInterval);
		OutputDebugString( test.GetValue().c_str() );
		OutputDebugString( "\n" );
		break;
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