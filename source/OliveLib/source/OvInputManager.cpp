#include "OvInputManager.h"
#include "OliveValue.h"

#pragma comment(lib, "DInput8.lib")
#pragma comment(lib, "Dxguid.lib")

OvInputManager::OvInputManager()
: m_direct_input( NULL )
, m_window_handle( NULL )
, m_keyboard_device( NULL )
, m_mouse_device( NULL )
{
	OvUInt index = 0;

	index = MAX_KEY;
	while ( index-- )
	{
		m_keyboard_state[ index ] = RELEASING;
	}
	ZeroMemory( &m_newKeyState[0], sizeof( m_newKeyState ) );
	

	index = BUTTON_COUNT;
	while ( index-- )
	{
		m_mouse_state[ index ] = RELEASING;
	}
	ZeroMemory( &m_new_mouse_state, sizeof( m_new_mouse_state ) );
	ZeroMemory( &m_mouse_state_time, sizeof( m_mouse_state_time ) );
}

OvInputManager::~OvInputManager()
{
	if ( m_keyboard_device )
	{
		m_keyboard_device->Unacquire();
		m_keyboard_device->Release();
	}
	if ( m_mouse_device )
	{
		m_mouse_device->Unacquire();
		m_mouse_device->Release();
	}
}

OvBool OvInputManager::IsStateOfKey( byte dik_key, OvUInt state )
{
	OvUInt key = m_keyboard_state[dik_key];
	OvBool result = (key & state);
	return result;
}

OvBool OvInputManager::IsStateOfMouse( MOUSE_BUTTON button, OvUInt state )
{
	OvUInt key = m_mouse_state[button];
	OvBool result = (key & state);
	return result;
}

OvPoint3 OvInputManager::GetMouseMoveDelta()
{
	OvPoint3 moveDelta;
	moveDelta.x = (OvFloat)m_new_mouse_state.lX;
	moveDelta.y = (OvFloat)m_new_mouse_state.lY;
	moveDelta.z = (OvFloat)m_new_mouse_state.lZ;
	return moveDelta;
}

void OvInputManager::_update()
{
	//!< 한프레임에 여러번 장치에 대한 요청을 하지 않는다.
	//!< 얻으면 좋고, 못얻으면 다음번 프레임에 얻길 바랄뿐.
	//!< 이곳에서 불필요한 공회전이 일어나길 바라지 않는다. 
	//!< (필요하면 쓰레드를 사용하겠지만
	//!< 그 방법이 이 방법보다 그닥 큰 효율이 있을것 같진 않다.)
	/*while ( hr == DIERR_INPUTLOST )
	{
		hr = m_keyboard_device->Acquire();
	}*/

	DWORD time = GetTickCount();
	_update_input_option( time );
	_update_keyboard_state( time );
	_update_mouse_state( time );

}

void OvInputManager::_update_input_option( DWORD time )
{
	//!< 옵션 변경이 있을때만 장치 요청을 포기하고 옵션을 변경한다.
	if ( m_input_options_backup != m_input_options )
	{
		// 옵션을 변경하기 위해선, 장치에 대한 요청을 포기해야 한다.
		m_keyboard_device->Unacquire();
		m_mouse_device->Unacquire();

		if ( IsChangedOption( OPT_CAPTURE_MOUSE ) )
		{
			OvUInt exculsivity = GetInputOption( OPT_CAPTURE_MOUSE )? DISCL_EXCLUSIVE:DISCL_NONEXCLUSIVE;
			m_mouse_device->SetCooperativeLevel( m_window_handle, exculsivity |
				DISCL_FOREGROUND);
		}

		m_input_options_backup = m_input_options;
	}

}

void OvInputManager::_update_keyboard_state( DWORD time )
{
	if ( m_keyboard_device && SUCCEEDED( m_keyboard_device->Acquire() ) )
	{
		m_keyboard_device->GetDeviceState( sizeof( m_newKeyState ), &(m_newKeyState[0]) );
		DWORD click_limit_time = 1000;

		unsigned i = MAX_KEY; 
		while ( i-- )
		{
			BUTTON_STATE new_state = (m_newKeyState[i] == 0x80)? PRESSED : RELEASED;
			BUTTON_STATE old_state = m_keyboard_state[i];
			if( (old_state == PRESSED || old_state == PRESSING) && new_state == PRESSED )
			{
				new_state = PRESSING;
			}
			else if( (old_state == RELEASED || old_state == RELEASING)  && new_state == RELEASED )
			{
				new_state = RELEASING;
			}
			m_keyboard_state_time[i][new_state] = time;

			if ( old_state != new_state )
			{
				// CLICK 에 대함 검출
				if ( new_state == RELEASED && old_state != CLICKED)
				{
					DWORD released_time = m_keyboard_state_time[i][RELEASED];
					DWORD pressed_time	= m_keyboard_state_time[i][PRESSED];
					if ( released_time - pressed_time < click_limit_time )
					{
						new_state = CLICKED;
					}
				}
				m_keyboard_state[i] = new_state;
				m_keyboard_state_time[i][new_state] = time;
			}
		}
	}
	else
	{
		unsigned i = MAX_KEY; 
		while ( i-- )
		{
			m_keyboard_state[i] = RELEASING;
		}
	}
}

void OvInputManager::_update_mouse_state( DWORD time )
{
	if ( m_mouse_device && SUCCEEDED( m_mouse_device->Acquire() ) )
	{
		m_mouse_device->GetDeviceState( sizeof( m_new_mouse_state ), &(m_new_mouse_state) );

		DWORD click_limit_time = 1000;

		unsigned i = BUTTON_COUNT; 
		while ( i-- )
		{
			BUTTON_STATE new_state = (m_new_mouse_state.rgbButtons[i] == 0x80)? PRESSED : RELEASED;
			BUTTON_STATE old_state = m_mouse_state[i];
			if( (old_state == PRESSED || old_state == PRESSING) && new_state == PRESSED )
			{
				new_state = PRESSING;
			}
			else if( (old_state == RELEASED || old_state == RELEASING)  && new_state == RELEASED )
			{
				new_state = RELEASING;
			}
			m_mouse_state_time[i][new_state] = time;

			if ( old_state != new_state )
			{
				// CLICK 에 대함 검출
				if ( new_state == RELEASED && old_state != CLICKED)
				{
					if ( m_mouse_state_time[i][RELEASED] - m_mouse_state_time[i][PRESSED] < click_limit_time )
					{
						new_state = CLICKED;
					}
				}
				m_mouse_state[i] = new_state;
				m_mouse_state_time[i][new_state] = time;
			}
		}
	}
	else
	{
		unsigned i = BUTTON_COUNT; 
		while ( i-- )
		{
			m_mouse_state[i] = RELEASING;
		}
	}
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
		m_mouse_device->SetCooperativeLevel( hWnd, DISCL_NONEXCLUSIVE |
			DISCL_FOREGROUND);

		m_window_handle = hWnd;
	}


}

void OvInputManager::SetInputOption( INPUT_OPTION opt, OvBool check )
{
	m_input_options.SetFlag( opt, check );
}

OvBool OvInputManager::GetInputOption( INPUT_OPTION opt )
{
	return m_input_options.GetFlag( opt );
}

OvBool OvInputManager::IsChangedOption( INPUT_OPTION opt )
{
	return ( m_input_options_backup.GetFlag( opt ) != m_input_options.GetFlag( opt ) );
}