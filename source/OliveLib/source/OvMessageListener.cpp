#include "OvMessageListener.h"
#include "OvMessageManager.h"
OvRTTI_IMPL(OvMessageListener);

OvMessageListener::OvMessageListener()
: m_messageProcessed( true )
{
	OvWinMsgManager::GetInstance()->_register_listener( this );
}

OvMessageListener::~OvMessageListener()
{
	OvWinMsgManager::GetInstance()->_remove_listener( this );
}

void OvMessageListener::Update( float _fElapse )
{
	if ( ! m_messageProcessed )
	{
		MessageListen
			( m_message.hwnd
			, m_message.message
			, m_message.wparam
			, m_message.lparam );
		m_messageProcessed = true;
	}
}

void OvMessageListener::_push_message( const InputMessage& message )
{
	m_messageProcessed = false;
	m_message = message;
}