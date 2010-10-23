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
OvPoint2 OvInputManager::GetCurrentMousePos()
{
	POINT cursorPos;
	GetCursorPos( &cursorPos );
	OvPoint2 newPos( cursorPos.x, cursorPos.y );
	return newPos;
}
