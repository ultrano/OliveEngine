#include "OvInputManager.h"
#include "OliveValue.h"

#pragma comment(lib, "DInput8.lib")
#pragma comment(lib, "Dxguid.lib")

OvInputManager::OvInputManager()
{
}

OvInputManager::~OvInputManager()
{
	if ( m_keyboard_device )
	{
		m_keyboard_device->Unacquire();
		m_keyboard_device->Release();
	}
}

bool OvInputManager::IsPushed( byte dik_key )
{
	return GetInstance()->m_newKeyState[dik_key] & 0x80;
}

bool OvInputManager::IsStateOf( MOUSE_BUTTON button, BUTTON_STATE state )
{
	return ( GetInstance()->m_new_mouse_state.rgbButtons[ button ] == 0x80 );
}

OvPoint3 OvInputManager::GetMouseMoveDelta()
{
	OvPoint3 moveDelta;
	moveDelta.x = (float)GetInstance()->m_new_mouse_state.lX;
	moveDelta.y = (float)GetInstance()->m_new_mouse_state.lY;
	moveDelta.z = (float)GetInstance()->m_new_mouse_state.lZ;
	return moveDelta;
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

void OvInputManager::_update()
{
	if ( NULL == m_keyboard_device )
	{
		return ;
	}

	HRESULT hr = m_keyboard_device->Acquire();
	while ( hr == DIERR_INPUTLOST )
	{
		hr = m_keyboard_device->Acquire();
	}
	m_keyboard_device->GetDeviceState( sizeof( m_newKeyState ), &(m_newKeyState[0]) );

	hr = m_mouse_device->Acquire();
	while ( hr == DIERR_INPUTLOST )
	{
		hr = m_mouse_device->Acquire();
	}
	m_mouse_device->GetDeviceState( sizeof( m_new_mouse_state ), &(m_new_mouse_state) );
}

void OvInputManager::_initialize( HWND hWnd )
{
	HRESULT hr = E_FAIL;
	hr = DirectInput8Create( GetModuleHandle(NULL)
		, DIRECTINPUT_VERSION
		, IID_IDirectInput8W
		, ( VOID** ) &m_direct_input
		, NULL);

	if ( SUCCEEDED( hr ) )
	{
		m_direct_input->CreateDevice( GUID_SysKeyboard
									, &m_keyboard_device
									, NULL );

		m_keyboard_device->SetDataFormat( &c_dfDIKeyboard );

		m_keyboard_device->SetCooperativeLevel(hWnd, DISCL_EXCLUSIVE |
			DISCL_FOREGROUND);

		m_direct_input->CreateDevice( GUID_SysMouse
									, &m_mouse_device
									, NULL);
		m_mouse_device->SetDataFormat( &c_dfDIMouse2 );
		m_mouse_device->SetCooperativeLevel( hWnd, DISCL_EXCLUSIVE |
			DISCL_FOREGROUND);
	}


}