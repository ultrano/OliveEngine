#pragma once
#include "OvUtility.h"
#include "OvSingleton.h"
#include "OvPoint2.h"
#include <windows.h>
#include <list>

class OvWinMsgManager : public OvSingletonBase< OvWinMsgManager >
{
	friend class OvMessageListener;
	typedef std::list<OvMessageListener*>	listener_list;
public:
	OvWinMsgManager();
	~OvWinMsgManager();

public:

	static bool	ListenMessage( HWND hWnd, UINT message, WPARAM wParam, LPARAM lParam);

public:

	OvPoint2	GetLastMousePoint();
	OvPoint2	GetMouseInterval();

	void	_update();
private:

	bool	_listenMessage( HWND hWnd, UINT message, WPARAM wParam, LPARAM lParam);
	void	_register_listener( OvMessageListener* listener );
	void	_remove_listener( OvMessageListener* listener );

private:
	listener_list	m_listenerList;
	OvPoint2	m_lastMousePoint;
	OvPoint2	m_mouseMoveInterval;
};