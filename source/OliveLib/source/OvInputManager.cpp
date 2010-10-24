#include "OvInputManager.h"
#include "OliveValue.h"

OvInputManager::OvInputManager()
{

}

OvInputManager::~OvInputManager()
{

}

bool OvInputManager::IsPushed( int vk_key )
{
	return GetKeyState( vk_key ) < 0;
}

bool OvInputManager::IsStateOf( MOUSE_BUTTON button, BUTTON_STATE state )
{
	return ( GetInstance()->m_buttonState[ button ].curr_state == state );
}

OvPoint2 OvInputManager::GetCurrentMousePos()
{
	POINT cursorPos;
	GetCursorPos( &cursorPos );
	OvPoint2 newPos( cursorPos.x, cursorPos.y );
	return newPos;
}

void OvInputManager::_notify_mouse_state( MOUSE_BUTTON button, BUTTON_STATE curr_state )
{
	DWORD temp_time = 1000;/*one second*/

	button_state_info& state_info = m_buttonState[ button ];
	DWORD curr_time = GetTickCount();
	DWORD notify_term = curr_time - state_info.refresh_time;
	BUTTON_STATE prev_state = state_info.curr_state;

	state_info.curr_state = curr_state;
	state_info.refresh_time = curr_time;

	if ( curr_state == RELEASED 
		&& prev_state == PRESSED 
		&& notify_term < temp_time )
	{
		state_info.curr_state = CLICKED;
	}

}

// click, double click 같은 경우 지속되면 안되는 상태기 때문에 풀어줘야 한다.
void OvInputManager::_clear_click_state()
{
	for ( unsigned i = 0 ; i < (unsigned) BUTTON_COUNT ; ++i )
	{
		button_state_info& state_info = m_buttonState[ i ];

		if ( state_info.curr_state == CLICKED
			|| state_info.curr_state == DBCLICKED )
		{
			_notify_mouse_state( (MOUSE_BUTTON)i, RELEASED );
		}
	}
}