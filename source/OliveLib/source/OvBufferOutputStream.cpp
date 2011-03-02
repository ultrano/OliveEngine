#include "OvBufferOutputStream.h"
#include "OvBuffer.h"

OvBufferOutputStream::OvBufferOutputStream( OvBuffer * buffer )
: m_buffer( buffer )
, m_write_caret( 0 )
{

}

OvBufferOutputStream::OvBufferOutputStream( OvBufferSPtr buffer )
: m_buffer( buffer )
, m_write_caret( 0 )
{

}

OvSize OvBufferOutputStream::WriteBytes( OvByte * src, OvSize write_size )
{
	OvSize src_size = m_buffer->Size() - m_write_caret;
	if ( src_size < write_size )
	{
		OvSize increment = m_buffer->Increment();
		m_buffer->Establish( ( write_size / increment ) + 1 );
	}
	if ( OvByte * buf = m_buffer->Pointer() )
	{
		memcpy( buf + m_write_caret, src, write_size );
		m_write_caret += write_size;
		return write_size;
	}
	return 0;
}

OvSize OvBufferOutputStream::Skip( OvSize skip_size )
{
	if ( skip_size > 0 )
	{
		OvSize src_size = m_buffer->Size() - m_write_caret;
		if ( skip_size = min( src_size, skip_size ) )
		{
			m_write_caret += skip_size;
			return skip_size;
		}
	}
	return 0;
}

OvBufferSPtr OvBufferOutputStream::GetBuffer()
{
	return m_buffer;
}
