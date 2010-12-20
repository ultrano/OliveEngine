#pragma once
#include "OvXComponent.h"
#include <list>

class OvMessageListener : public OvXComponent
{
	OvRTTI_DECL(OvMessageListener);
	friend class OvMessageManager;
public:
	struct InputMessage
	{
		InputMessage(){};
		InputMessage(HWND in_hwnd, UINT in_message, WPARAM in_wparam, LPARAM in_lparam)
			: hwnd(in_hwnd),message(in_message),wparam(in_wparam),lparam(in_lparam){};
		HWND hwnd;
		UINT message;
		WPARAM wparam;
		LPARAM lparam;
	};

	OvMessageListener();
	~OvMessageListener();

	virtual OvBool MessageListen(HWND hwnd, UINT message, WPARAM wparam, LPARAM lparam) = 0;

private:

	virtual void	Update(OvFloat _fElapse) override;
	void	_push_message( const InputMessage& message );

private:
	enum {MSG_QUEUE_SIZE = 10};
	InputMessage m_message;
	OvBool m_messageProcessed;
};