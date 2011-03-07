#pragma once
#include "OvInputStream.h"

OvREF_POINTER(OvBuffer);
OvREF_POINTER(OvBufferInputStream);
class OvBufferInputStream : public OvInputStream
{
	OvRTTI_DECL( OvBufferInputStream );
public:

	OvBufferInputStream( OvBuffer * buffer );
	OvBufferInputStream( OvBufferSPtr buffer );

	virtual OvSize ReadBytes( OvByte * dest, OvSize dest_size ) override;
	virtual OvSize Skip( OvSize offset ) override;

	OvBufferSPtr GetBuffer();

private:

	OvBufferSPtr m_buffer;
	OvSize		 m_read_caret;
};