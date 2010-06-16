#include "OvExtraProperty.h"

using namespace OvExtraProperty;
OvRTTI_IMPL_ROOT(Value);

OvRTTI_IMPL(Float);
OvRTTI_IMPL(Integer);
OvRTTI_IMPL(String);

OvRTTF_CONSTRUCTOR_IMPL(Float){};
OvRTTF_CONSTRUCTOR_IMPL(Integer){};
OvRTTF_CONSTRUCTOR_IMPL(String){};

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