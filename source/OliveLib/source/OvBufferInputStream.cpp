#include "OvBufferInputStream.h"
#include "OvBuffer.h"
OvRTTI_IMPL_ROOT(OvBufferInputStream);

OvBufferInputStream::OvBufferInputStream( OvBuffer * buffer )
: m_buffer( buffer )
, m_read_caret( 0 )
{

}

OvBufferInputStream::OvBufferInputStream( OvBufferSPtr buffer )
: m_buffer( buffer )
, m_read_caret( 0 )
{

}

OvSize OvBufferInputStream::ReadBytes( OvByte * dest, OvSize dest_size )
{
	if ( OvByte * buf = m_buffer->Pointer() )
	{
		OvSize src_size = m_buffer->Size() - m_read_caret;
		if ( OvSize cpy_size = min( src_size, dest_size ) )
		{
			memcpy( dest, buf + m_read_caret, cpy_size );
			m_read_caret += cpy_size;
			return cpy_size;
		}
	}
	return 0;
}

OvSize OvBufferInputStream::Skip( OvSize offset )
{
	OvSize src_size = 0;
	if ( offset > 0 )
	{
		src_size = m_buffer->Size() - m_read_caret;
		offset = min( src_size, offset );
	}
	else
	{
		src_size = -m_read_caret;
		offset = max( src_size, offset );
	}

	m_read_caret += offset;
	return offset;
}


OvBufferSPtr OvBufferInputStream::GetBuffer()
{
	return m_buffer;
}