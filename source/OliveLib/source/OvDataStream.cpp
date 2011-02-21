#include "OvDataStream.h"
#include "OvUtility.h"
using namespace std;

OvDataStream::OvDataStream( const OvString& buf )
: m_read_caret( 0 )
, m_buffer( buf )
{

}

OvDataStream::OvDataStream( size_t reserve_size )
: m_read_caret( 0 )
{
	if ( reserve_size > 0 )
	{
		m_buffer.resize( reserve_size );
	}
}

OvDataStream::~OvDataStream()
{
	m_buffer.resize( 0 );
	m_buffer.clear();
	m_read_caret = 0;
}

const OvChar* OvDataStream::Ptr()
{
	return m_buffer.data();
}

size_t OvDataStream::Size()
{
	return m_buffer.size();
}

const OvChar* OvDataStream::CaretPtr()
{
	if ( CaretPos() < Size() )
	{
		const OvChar* buf = Ptr();
		return &(buf[ CaretPos() ]);
	}
	return NULL;
}

size_t OvDataStream::CaretPos()
{
	return m_read_caret;
}

OvUInt OvDataStream::Read( OvString& buf, OvUInt read_size )
{
	if ( Size() )
	{
		buf = m_buffer.substr( m_read_caret, read_size );
		m_read_caret += read_size;
	}
	return read_size;
}

OvUInt OvDataStream::ReadLine( OvString& buf )
{
	OvString delimiter = "\n";
	OvString::size_type pos = m_buffer.find( delimiter, m_read_caret );
	if ( pos != OvString::npos )
	{
		// delimiter 까지 포함시키기 위해 1을 더함
		OvSize sz = 1 + pos - m_read_caret;
		buf = m_buffer.substr( m_read_caret, sz );
		m_read_caret += sz;
		buf = OU::string::trim( buf );
		return sz;
	}
	return 0;
}