#include "OvInputEventListener.h"
#include "OvInputDevice.h"
OvRTTI_IMPL(OvInputEventListener);

OvInputEventListener::OvInputEventListener()
{
	OvInputDevice::GetInstance()->_register_listener( this );
}

OvInputEventListener::~OvInputEventListener()
{
	OvInputDevice::GetInstance()->_remove_listener( this );
}

void OvInputEventListener::Update( float _fElapse )
{
	for each( const InputMessage& message in m_inputQueue )
	{
		MessageListen
			( message.hwnd
			, message.message
			, message.wparam
			, message.lparam );
	}
	m_inputQueue.clear();
}

void OvInputEventListener::_push_message( const InputMessage& message )
{
	if (m_inputQueue.size() > MSG_QUEUE_SIZE)
	{
		m_inputQueue.pop_front();
	}
	m_inputQueue.push_back( message );
}