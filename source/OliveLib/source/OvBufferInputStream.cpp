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
OvBool OvBufferInputStream::ReadByte( OvByte & read )
{
	return !!ReadBytes( &read, sizeof(OvByte) );
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

OvBufferSPtr OvBufferInputStream::GetBuffer()
{
	return m_buffer;
}
