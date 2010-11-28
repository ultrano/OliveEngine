#pragma once
#include "OvSingleton.h"
#include "OvPoint2.h"
#include "OvPoint3.h"
#include <dinput.h>


enum MOUSE_BUTTON { L_BUTTON, R_BUTTON, M_BUTTON, BUTTON_COUNT };
enum BUTTON_STATE { PRESSED, RELEASED, PRESSING, CLICKED, DBCLICKED };

class OvInputManager : public OvSingletonBase< OvInputManager >
{
	friend class OvWinMsgManager;
	friend class OvRenderer;
	struct button_state_info 
	{
		BUTTON_STATE 	curr_state;
		DWORD			refresh_time;
	};
public:
	OvInputManager();
	~OvInputManager();

	static bool IsPushed( byte dik_key );
	static bool IsStateOf( MOUSE_BUTTON button, BUTTON_STATE state );
	static OvPoint3 GetMouseMoveDelta();

	void	_update();
private:

	void	_notify_mouse_state( MOUSE_BUTTON button, BUTTON_STATE state );
	void	_clear_click_state();
	void	_initialize( HWND hWnd );

private:

	enum {MAX_KEY = 256};

	button_state_info m_buttonState[ BUTTON_COUNT ];
	LPDIRECTINPUT8	m_direct_input;

	LPDIRECTINPUTDEVICE8 m_keyboard_device;
	byte m_newKeyState[ MAX_KEY ];
	byte m_oldKeyState[ MAX_KEY ];

	LPDIRECTINPUTDEVICE8 m_mouse_device;
	DIMOUSESTATE2		 m_new_mouse_state;
};