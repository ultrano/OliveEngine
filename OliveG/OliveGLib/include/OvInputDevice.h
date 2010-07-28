#pragma once
#include "OvUtility.h"
#include "OvSingleton.h"
#include "OvPoint2.h"
#include <windows.h>
#include <list>

class OvInputDevice : public OvSingletonBase< OvInputDevice >
{
	friend class OvInputEventListener;
	typedef std::list<OvInputEventListener*>	listener_list;
public:
	OvInputDevice();
	~OvInputDevice();

public:

	static bool	ListenMessage( HWND hWnd, UINT message, WPARAM wParam, LPARAM lParam);

public:

	OvPoint2	GetLastMousePoint();
	OvPoint2	GetMouseInterval();

private:

	bool	_listenMessage( HWND hWnd, UINT message, WPARAM wParam, LPARAM lParam);
	void	_register_listener( OvInputEventListener* listener );
	void	_remove_listener( OvInputEventListener* listener );

private:
	listener_list	m_listenerList;
	OvPoint2	m_lastMousePoint;
	OvPoint2	m_mouseMoveInterval;
};