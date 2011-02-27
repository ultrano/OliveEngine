#include "OvBuffer.h"

OvBufferSPtr OvBuffer::CreateBuffer( OvSize capacity, OvSize increment )
{
	OvBufferSPtr buffer = OvNew OvBuffer();
	buffer->m_buf = new OvByte[ capacity ];
	buffer->m_size = capacity;
	buffer->m_increment = increment;
	return buffer;
}

OvBuffer::OvBuffer()
{

}

OvByte * OvBuffer::Pointer()
{
	return m_buf.GetRear();
}

OvSize OvBuffer::Size()
{
	return m_size;
}

OvSize OvBuffer::Increment()
{
	return m_increment;
}

void OvBuffer::Establish( OvUInt times )
{
	if ( times > 0 )
	{
		OvSize old_size = m_size;
		OvSize new_size = m_size + ( m_increment * times );

		OvByte* old_buf = m_buf.GetRear();
		OvByte* new_buf = new OvByte[ new_size ];

		memcpy( new_buf, old_buf, old_size );

		m_size = new_size;
		m_buf = new_buf;
	}
}