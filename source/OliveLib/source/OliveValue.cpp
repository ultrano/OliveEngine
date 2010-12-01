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
OvRTTI_IMPL(UserData);

//////////////////////////////////////////////////////////////////////////
#define REGIST_VALUE_TYPE_BEGINE OliveValue::Value*	OliveValue::Factory(const OvString& valueType){\
	if( valueType.empty() ){return NULL;}
#define	REGIST_VALUE_TYPE( classname ) else if( OvString(#classname) == valueType){return OvNew classname();}
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
	REGIST_VALUE_TYPE( ObjectID )
	REGIST_VALUE_TYPE( UserData )
REGIST_VALUE_TYPE_END
//////////////////////////////////////////////////////////////////////////

Value::Value()
{

}
Value::~Value()
{

}

void OliveValue::Value::SetValue( const char* expData )
{
	SetValue( OvString( expData ) );
}

//////////////////////////////////////////////////////////////////////////

void OliveValue::Bool::SetValue( const OvString& expData )
{
	if ( _stricmp( "0",expData.c_str() ) == 0 || _stricmp( "false",expData.c_str() ) == 0 )
	{
		m_value = false;
	}
	else if ( _stricmp( "1",expData.c_str() ) == 0 || _stricmp( "true",expData.c_str() ) == 0 )
	{
		m_value = true;
	}
}

OvString OliveValue::Bool::GetValue()
{
	return OvString( OvFormatString( "%d", m_value ) );
}

void OliveValue::Bool::SetBool( OvBool expData )
{
	m_value = expData;
}

OvBool OliveValue::Bool::GetBool()
{
	return m_value;
}

//////////////////////////////////////////////////////////////////////////
void			Float::SetValue( const OvString& expData )
{
	sscanf_s( expData.c_str(), "%f", &m_value );
}
OvString			Float::GetValue()
{
	return OvString( OvFormatString( "%f", m_value ) );
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
void			Point2::SetValue( const OvString& expData )
{
	sscanf_s( expData.c_str(), "%f,%f", &m_value.x, &m_value.y );
}
OvString			Point2::GetValue()
{
	return OvString( OvFormatString( "%f,%f", m_value.x, m_value.y ) );
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
void			Point3::SetValue( const OvString& expData )
{
	sscanf_s( expData.c_str(), "%f,%f,%f", &m_value.x, &m_value.y, &m_value.z );
}
OvString			Point3::GetValue()
{
	return OvString( OvFormatString( "%f,%f,%f", m_value.x, m_value.y, m_value.z ) );
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
void				Quaternion::SetValue( const OvString& expData )
{
	sscanf_s( expData.c_str(), "%f,%f,%f,%f", &m_value.x, &m_value.y, &m_value.z, &m_value.w );
}
OvString				Quaternion::GetValue()
{
	return OvString( OvFormatString( "%f,%f,%f,%f", m_value.x, m_value.y, m_value.z, m_value.w ) );
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
void			Integer::SetValue( const OvString& expData )
{
	sscanf_s( expData.c_str(), "%d", &m_value );
}
OvString			Integer::GetValue()
{
	return OvString( OvFormatString( "%d", m_value ) );
}
void			Integer::SetInteger( OvInt expValue )
{
	m_value = expValue;
}
OvInt				Integer::GetInteger()
{
	return m_value;
}
//////////////////////////////////////////////////////////////////////////

//////////////////////////////////////////////////////////////////////////
void			String::SetValue( const OvString& expData )
{
	m_value = expData;
}
OvString			String::GetValue()
{
	return m_value;
}
void			String::SetString( const OvString& expValue )
{
	m_value = expValue;
}
const OvString&	String::GetString()
{
	return m_value;
}
//////////////////////////////////////////////////////////////////////////

//////////////////////////////////////////////////////////////////////////
void			ObjectID::SetValue( const OvString& expData )
{
	OvObjectID::id_core_type core_id;
	sscanf_s( expData.c_str(), "%d", &core_id );
	m_value = OvObjectID( core_id );
}
OvString			ObjectID::GetValue()
{
	return OvString( OvFormatString( "%d", m_value ) );
}
void			ObjectID::SetObjectID( const OvObjectID& expValue )
{
	m_value = expValue;
}
const OvObjectID& ObjectID::GetObjectID()
{
	return m_value;
}
//////////////////////////////////////////////////////////////////////////

//////////////////////////////////////////////////////////////////////////

void OliveValue::UserData::SetValue( const OvString& expData )
{
	sscanf_s( expData.c_str(), "%p", &m_value );
}

OvString OliveValue::UserData::GetValue()
{
	return OvString( OvFormatString( "%p", m_value ) );
}

void OliveValue::UserData::SetUserData( void* userData )
{
	m_value = userData;
}

void* OliveValue::UserData::GetUserData()
{
	return m_value;
}