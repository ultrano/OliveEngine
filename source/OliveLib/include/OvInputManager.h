#pragma once
#include "OvSingleton.h"
#include "OvPoint2.h"

enum MOUSE_BUTTON { L_BUTTON, M_BUTTON, R_BUTTON, BUTTON_COUNT };
enum BUTTON_STATE { PRESSED, RELEASED, CLICKED, DBCLICKED };

class OvInputManager : public OvSingletonBase< OvInputManager >
{
	friend class OvWinMsgManager;
	struct button_state_info 
	{
		BUTTON_STATE 	curr_state;
		DWORD			refresh_time;
	};
public:
	OvInputManager();
	~OvInputManager();

	static bool IsPushed( int vk_key );
	static bool IsStateOf( MOUSE_BUTTON button, BUTTON_STATE state );
	static OvPoint2 GetCurrentMousePos();
	
private:

	void	_notify_mouse_state( MOUSE_BUTTON button, BUTTON_STATE state );
	void	_clear_click_state();

private:

	button_state_info m_buttonState[ BUTTON_COUNT ];

};