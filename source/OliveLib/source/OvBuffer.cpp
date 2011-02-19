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

void OvBuffer::Establish( OvUInt count )
{
	m_size += m_increment * count;
	m_buf = new OvByte[ m_size ];
}