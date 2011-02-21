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

	virtual OvBool ReadByte( OvByte & read ) override;
	virtual OvSize ReadBytes( OvByte * dest, OvSize dest_size ) override;

	template<typename T>
	OvBool	Read( T& data )
	{
		return !!ReadBytes( (OvByte*)&data, sizeof(T) );
	};

	OvBool Read( OvString& data )
	{
		OvSize size = 0;
		Read( size );
		data.resize( size );
		return !!ReadBytes( (OvByte*)&data[0], size );
	};

	OvBufferSPtr GetBuffer();

private:

	OvBufferSPtr m_buffer;
	OvSize		 m_read_caret;
};