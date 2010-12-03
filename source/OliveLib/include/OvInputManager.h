#pragma once
#include "OvSingleton.h"
#include "OvPoint2.h"
#include "OvPoint3.h"
#include <dinput.h>


enum MOUSE_BUTTON { L_BUTTON, R_BUTTON, M_BUTTON, BUTTON_COUNT = 8 };
enum BUTTON_STATE 
{ 
	RELEASING	= 1 << 1, 
	RELEASED	= 1 << 2, 
	PRESSING	= 1 << 3, 
	PRESSED		= 1 << 4, 
	CLICKED		= 1 << 5, 
	STATE_COUNT	= 6			};

class OvInputManager : public OvSingletonBase< OvInputManager >
{
	friend class OliveDevice;
	friend class OvRenderer;
public:
	OvInputManager();
	~OvInputManager();

	OvBool IsStateOfKey( byte dik_key, OvUInt state );
	OvBool IsStateOfMouse( MOUSE_BUTTON button, OvUInt state );
	OvPoint3 GetMouseMoveDelta();

private:

	void	_initialize( HWND hWnd );
	void	_update();

	void	_update_keyboard_state( DWORD time );
	void	_update_mouse_state( DWORD time );

private:

	enum {MAX_KEY = 256};

	LPDIRECTINPUT8	m_direct_input;

	LPDIRECTINPUTDEVICE8 m_keyboard_device;
	byte				 m_newKeyState[ MAX_KEY ];
	BUTTON_STATE		 m_keyboard_state[ MAX_KEY ];
	DWORD				 m_keyboard_state_time[MAX_KEY][STATE_COUNT];

	LPDIRECTINPUTDEVICE8 m_mouse_device;
	DIMOUSESTATE2		 m_new_mouse_state;
	BUTTON_STATE		 m_mouse_state[BUTTON_COUNT];
	DWORD				 m_mouse_state_time[BUTTON_COUNT][STATE_COUNT];
};