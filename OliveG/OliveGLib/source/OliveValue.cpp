#include "OliveValue.h"

using namespace OliveValue;
OvRTTI_IMPL_ROOT(Value);

OvRTTI_IMPL(Float);
OvRTTI_IMPL(Integer);
OvRTTI_IMPL(String);


//////////////////////////////////////////////////////////////////////////
REGIST_VALUE_TYPE_BEGINE
	REGIST_VALUE_TYPE( Float )
	REGIST_VALUE_TYPE( Integer )
	REGIST_VALUE_TYPE( String )
REGIST_VALUE_TYPE_END
//////////////////////////////////////////////////////////////////////////


#include <boost/lexical_cast.hpp>

Value::Value()
{

}
Value::~Value()
{

}

//////////////////////////////////////////////////////////////////////////
void			Float::SetValue( const string& expData )
{
	m_value = boost::lexical_cast<float>(expData);
}
string			Float::GetValue()
{
	return boost::lexical_cast<string>(m_value);
}
void			Float::SetFloat( float expValue )
{
	m_value = expValue;
}
float			Float::GetFloat()
{
	return m_value;
}
//////////////////////////////////////////////////////////////////////////

//////////////////////////////////////////////////////////////////////////
void			Integer::SetValue( const string& expData )
{
	m_value = boost::lexical_cast<int>(expData);
}
string			Integer::GetValue()
{
	return boost::lexical_cast<string>(m_value);
}
void			Integer::SetInteger( int expValue )
{
	m_value = expValue;
}
int				Integer::GetInteger()
{
	return m_value;
}
//////////////////////////////////////////////////////////////////////////

//////////////////////////////////////////////////////////////////////////
void			String::SetValue( const string& expData )
{
	m_value = expData;
}
string			String::GetValue()
{
	return m_value;
}
void			String::SetString( const string& expValue )
{
	m_value = expValue;
}
string				String::GetString()
{
	return m_value;
}
//////////////////////////////////////////////////////////////////////////