#include "OvDataStream.h"
using namespace std;

// 출처 : http://www.gammon.com.au/forum/bbshowpost.php?bbsubject_id=2896
// ㅜ_ㅜ 좋당.
#define SPACES " \t\r\n"

inline string trim_right (const string & s, const string & t = SPACES)
{ 
	string d (s); 
	string::size_type i (d.find_last_not_of (t));
	if (i == string::npos)
		return "";
	else
		return d.erase (d.find_last_not_of (t) + 1) ; 
}  // end of trim_right

inline string trim_left (const string & s, const string & t = SPACES) 
{ 
	string d (s); 
	return d.erase (0, s.find_first_not_of (t)) ; 
}  // end of trim_left

inline string trim (const string & s, const string & t = SPACES)
{ 
	string d (s); 
	return trim_left (trim_right (d, t), t) ; 
}  // end of trim

OvDataStream::OvDataStream( const std::string& buf )
: m_read_caret( 0 )
, m_buffer( buf )
{

}

OvDataStream::OvDataStream( const char* data, size_t data_size )
: m_read_caret( 0 )
{
	if ( data && data_size )
	{
		m_buffer.resize( data_size );
		memcpy( (void*)m_buffer.at( 0 ), data, m_buffer.size() );
	}
}

OvDataStream::~OvDataStream()
{
	m_buffer.resize( 0 );
	m_buffer.clear();
	m_read_caret = 0;
}

const char* OvDataStream::Ptr()
{
	return m_buffer.data();
}

size_t OvDataStream::Size()
{
	return m_buffer.size();
}

const char* OvDataStream::CaretPtr()
{
	if ( CaretPos() < Size() )
	{
		const char* buf = Ptr();
		return &(buf[ CaretPos() ]);
	}
	return NULL;
}

size_t OvDataStream::CaretPos()
{
	return m_read_caret;
}

std::string& OvDataStream::Read( string& buf, size_t sz )
{
	if ( Size() )
	{
		buf = m_buffer.substr( m_read_caret, sz );
		m_read_caret += sz;
	}
	return buf;
}

std::string& OvDataStream::ReadLine( string& buf, string delimiter /*= '\n'*/ )
{
	string::size_type pos = m_buffer.find( delimiter, m_read_caret );
	if ( pos != string::npos )
	{
		// delimiter 까지 포함시키기 위해 1을 더함
		size_t sz = 1 + pos - m_read_caret;
		buf = m_buffer.substr( m_read_caret, sz );
		m_read_caret += sz;
		buf = trim( buf );
	}
	return buf;
}