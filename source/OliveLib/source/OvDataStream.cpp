#include "OvDataStream.h"
using namespace std;
OvRTTI_IMPL(OvDataStream);

// 출처 : http://www.gammon.com.au/forum/bbshowpost.php?bbsubject_id=2896
// ㅜ_ㅜ 좋당.
#define SPACES " \t\r\n"

inline OvString trim_right (const OvString & s, const OvString & t = SPACES)
{ 
	OvString d (s); 
	OvString::size_type i (d.find_last_not_of (t));
	if (i == OvString::npos)
		return "";
	else
		return d.erase (d.find_last_not_of (t) + 1) ; 
}  // end of trim_right

inline OvString trim_left (const OvString & s, const OvString & t = SPACES) 
{ 
	OvString d (s); 
	return d.erase (0, s.find_first_not_of (t)) ; 
}  // end of trim_left

inline OvString trim (const OvString & s, const OvString & t = SPACES)
{ 
	OvString d (s); 
	return trim_left (trim_right (d, t), t) ; 
}  // end of trim

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

OvInputStream& OvDataStream::Read( OvString& buf, OvUInt read_size )
{
	if ( Size() )
	{
		buf = m_buffer.substr( m_read_caret, read_size );
		m_read_caret += read_size;
	}
	return *this;
}

OvInputStream& OvDataStream::ReadLine( OvString& buf )
{
	OvString delimiter = "\n";
	OvString::size_type pos = m_buffer.find( delimiter, m_read_caret );
	if ( pos != OvString::npos )
	{
		// delimiter 까지 포함시키기 위해 1을 더함
		size_t sz = 1 + pos - m_read_caret;
		buf = m_buffer.substr( m_read_caret, sz );
		m_read_caret += sz;
		buf = trim( buf );
	}
	return *this;
}