#include "OvMessageListener.h"
#include "OvMessageManager.h"
OvRTTI_IMPL(OvMessageListener);

OvMessageListener::OvMessageListener()
{
	OvMessageManager::GetInstance()->_register_listener( this );
}

OvMessageListener::~OvMessageListener()
{
	OvMessageManager::GetInstance()->_remove_listener( this );
}

void OvMessageListener::Update( float _fElapse )
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

void OvMessageListener::_push_message( const InputMessage& message )
{
	if (m_inputQueue.size() > MSG_QUEUE_SIZE)
	{
		m_inputQueue.pop_front();
	}
	m_inputQueue.push_back( message );
}