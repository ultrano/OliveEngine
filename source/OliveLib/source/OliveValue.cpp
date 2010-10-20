#include "OliveValue.h"
#include "OvStringUtility.h"

using namespace OliveValue;
OvRTTI_IMPL_ROOT(Value);

OvRTTI_IMPL(Bool);
OvRTTI_IMPL(Float);
OvRTTI_IMPL(Point2);
OvRTTI_IMPL(Point3);
OvRTTI_IMPL(Quaternion);
OvRTTI_IMPL(Integer);
OvRTTI_IMPL(String);
OvRTTI_IMPL(ObjectID);

//////////////////////////////////////////////////////////////////////////
#define REGIST_VALUE_TYPE_BEGINE OliveValue::Value*	OliveValue::Factory(const std::string& valueType){\
	if( valueType.empty() ){return NULL;}
#define	REGIST_VALUE_TYPE( classname ) else if( std::string(#classname) == valueType){return OvNew classname();}
#define REGIST_VALUE_TYPE_END	return NULL;};
//////////////////////////////////////////////////////////////////////////
REGIST_VALUE_TYPE_BEGINE
	REGIST_VALUE_TYPE( Bool )
	REGIST_VALUE_TYPE( Float )
	REGIST_VALUE_TYPE( Point2 )
	REGIST_VALUE_TYPE( Point3 )
	REGIST_VALUE_TYPE( Quaternion )
	REGIST_VALUE_TYPE( Integer )
	REGIST_VALUE_TYPE( String )
REGIST_VALUE_TYPE_END
//////////////////////////////////////////////////////////////////////////

Value::Value()
{

}
Value::~Value()
{

}
//////////////////////////////////////////////////////////////////////////

void OliveValue::Bool::SetValue( const string& expData )
{
	if ( stricmp( "0",expData.c_str() ) == 0 || stricmp( "false",expData.c_str() ) == 0 )
	{
		m_value = false;
	}
	else if ( stricmp( "1",expData.c_str() ) == 0 || stricmp( "true",expData.c_str() ) == 0 )
	{
		m_value = true;
	}
}

std::string OliveValue::Bool::GetValue()
{
	return std::string( OvFormatString( "%d", m_value ) );
}

void OliveValue::Bool::SetBool( bool expData )
{
	m_value = expData;
}

bool OliveValue::Bool::GetBool()
{
	return m_value;
}

//////////////////////////////////////////////////////////////////////////
void			Float::SetValue( const string& expData )
{
	sscanf_s( expData.c_str(), "%f", &m_value );
}
string			Float::GetValue()
{
	return string( OvFormatString( "%f", m_value ) );
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
void			Point2::SetValue( const string& expData )
{
	sscanf_s( expData.c_str(), "%f,%f", &m_value.x, &m_value.y );
}
string			Point2::GetValue()
{
	return string( OvFormatString( "%f,%f", m_value.x, m_value.y ) );
}
void			Point2::SetPoint2( const OvPoint2& expValue )
{
	m_value = expValue;
}
void			Point2::SetPoint2( float x, float y )
{
	SetPoint2( OvPoint2( x, y ) );
}
const OvPoint2&	Point2::GetPoint2()
{
	return m_value;
}
//////////////////////////////////////////////////////////////////////////


//////////////////////////////////////////////////////////////////////////
void			Point3::SetValue( const string& expData )
{
	sscanf_s( expData.c_str(), "%f,%f,%f", &m_value.x, &m_value.y, &m_value.z );
}
string			Point3::GetValue()
{
	return string( OvFormatString( "%f,%f,%f", m_value.x, m_value.y, m_value.z ) );
}
void			Point3::SetPoint3( const OvPoint3& expValue )
{
	m_value = expValue;
}
void			Point3::SetPoint3( float x, float y, float z )
{
	SetPoint3( OvPoint3( x, y, z ) );
}
const OvPoint3&	Point3::GetPoint3()
{
	return m_value;
}
//////////////////////////////////////////////////////////////////////////


//////////////////////////////////////////////////////////////////////////
void				Quaternion::SetValue( const string& expData )
{
	sscanf_s( expData.c_str(), "%f,%f,%f,%f", &m_value.x, &m_value.y, &m_value.z, &m_value.w );
}
string				Quaternion::GetValue()
{
	return string( OvFormatString( "%f,%f,%f,%f", m_value.x, m_value.y, m_value.z, m_value.w ) );
}
void				Quaternion::SetQuaternion( const OvQuaternion& expValue )
{
	m_value = expValue;
}
void				Quaternion::SetQuaternion( float x, float y, float z, float w )
{
	SetQuaternion( OvQuaternion( x, y, z, w ) );
}
const OvQuaternion&	Quaternion::GetQuaternion()
{
	return m_value;
}
//////////////////////////////////////////////////////////////////////////


//////////////////////////////////////////////////////////////////////////
void			Integer::SetValue( const string& expData )
{
	sscanf_s( expData.c_str(), "%d", &m_value );
}
string			Integer::GetValue()
{
	return string( OvFormatString( "%d", m_value ) );
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
const string&	String::GetString()
{
	return m_value;
}
//////////////////////////////////////////////////////////////////////////

//////////////////////////////////////////////////////////////////////////
void			ObjectID::SetValue( const string& expData )
{
	OvObjectID::id_core_type core_id;
	sscanf_s( expData.c_str(), "%d", &core_id );
	m_value = OvObjectID( core_id );
}
string			ObjectID::GetValue()
{
	return string( OvFormatString( "%d", m_value ) );
}
void			ObjectID::SetObjectID( const OvObjectID& expValue )
{
	m_value = expValue;
}
const OvObjectID& ObjectID::GetObjectID()
{
	return m_value;
}