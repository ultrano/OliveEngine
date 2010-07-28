#pragma once
#include "OvXComponent.h"
#include <list>

class OvInputEventListener : public OvXComponent
{
	OvRTTI_DECL(OvInputEventListener);
	friend class OvInputDevice;
public:
	struct InputMessage
	{
		InputMessage(HWND in_hwnd, UINT in_message, WPARAM in_wparam, LPARAM in_lparam)
			: hwnd(in_hwnd),message(in_message),wparam(in_wparam),lparam(in_lparam){};
		HWND hwnd;
		UINT message;
		WPARAM wparam;
		LPARAM lparam;
	};

	OvInputEventListener();
	~OvInputEventListener();

	virtual bool MessageListen(HWND hwnd, UINT message, WPARAM wparam, LPARAM lparam) = 0;

private:

	virtual void	Update(float _fElapse) override;
	void	_push_message( const InputMessage& message );

private:
	enum {MSG_QUEUE_SIZE = 10};
	list<InputMessage>	m_inputQueue;
};