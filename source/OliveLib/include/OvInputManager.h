#pragma once
#include "OvSingleton.h"
#include "OvPoint2.h"

class OvInputManager : public OvSingletonBase< OvInputManager >
{
	friend class OvWinMsgManager;
public:
	OvInputManager();
	~OvInputManager();

	static bool IsPushed( int vk_key );

	static OvPoint2 GetCurrentMousePos();
	
private:


};