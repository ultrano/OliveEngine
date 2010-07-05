#pragma once
#include "OvUtility.h"
#include "OvSingleton.h"
#include "OvPoint2.h"
#include <windows.h>

class OvInputManager : public OvSingletonBase< OvInputManager >
{
public:
	OvInputManager();
	~OvInputManager();

public:

	static bool	ListenMessage( HWND hWnd, UINT message, WPARAM wParam, LPARAM lParam);

public:

	OvPoint2	GetLastMousePoint();
	OvPoint2	GetMouseInterval();

private:

	bool	_listenMessage( HWND hWnd, UINT message, WPARAM wParam, LPARAM lParam);

private:
	OvPoint2	m_lastMousePoint;
	OvPoint2	m_mouseMoveInterval;
};