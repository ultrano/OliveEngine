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

void OliveValue::Value::FromString( const char* expData )
{
	FromString( OvString( expData ) );
}

//////////////////////////////////////////////////////////////////////////

void OliveValue::Bool::FromString( const OvString& expData )
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

OvString OliveValue::Bool::ToString()
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
void			Float::FromString( const OvString& expData )
{
	sscanf_s( expData.c_str(), "%f", &m_value );
}
OvString			Float::ToString()
{
	return OvString( OvFormatString( "%f", m_value ) );
}
void			Float::SetFloat( OvFloat expValue )
{
	m_value = expValue;
}
OvFloat			Float::GetFloat()
{
	return m_value;
}
//////////////////////////////////////////////////////////////////////////

//////////////////////////////////////////////////////////////////////////
void			Point2::FromString( const OvString& expData )
{
	sscanf_s( expData.c_str(), "%f,%f", &m_value.x, &m_value.y );
}
OvString			Point2::ToString()
{
	return OvString( OvFormatString( "%f,%f", m_value.x, m_value.y ) );
}
void			Point2::SetPoint2( const OvPoint2& expValue )
{
	m_value = expValue;
}
void			Point2::SetPoint2( OvFloat x, OvFloat y )
{
	SetPoint2( OvPoint2( x, y ) );
}
const OvPoint2&	Point2::GetPoint2()
{
	return m_value;
}
//////////////////////////////////////////////////////////////////////////


//////////////////////////////////////////////////////////////////////////
void			Point3::FromString( const OvString& expData )
{
	sscanf_s( expData.c_str(), "%f,%f,%f", &m_value.x, &m_value.y, &m_value.z );
}
OvString			Point3::ToString()
{
	return OvString( OvFormatString( "%f,%f,%f", m_value.x, m_value.y, m_value.z ) );
}
void			Point3::SetPoint3( const OvPoint3& expValue )
{
	m_value = expValue;
}
void			Point3::SetPoint3( OvFloat x, OvFloat y, OvFloat z )
{
	SetPoint3( OvPoint3( x, y, z ) );
}
const OvPoint3&	Point3::GetPoint3()
{
	return m_value;
}
//////////////////////////////////////////////////////////////////////////


//////////////////////////////////////////////////////////////////////////
void				Quaternion::FromString( const OvString& expData )
{
	sscanf_s( expData.c_str(), "%f,%f,%f,%f", &m_value.x, &m_value.y, &m_value.z, &m_value.w );
}
OvString				Quaternion::ToString()
{
	return OvString( OvFormatString( "%f,%f,%f,%f", m_value.x, m_value.y, m_value.z, m_value.w ) );
}
void				Quaternion::SetQuaternion( const OvQuaternion& expValue )
{
	m_value = expValue;
}
void				Quaternion::SetQuaternion( OvFloat x, OvFloat y, OvFloat z, OvFloat w )
{
	SetQuaternion( OvQuaternion( x, y, z, w ) );
}
const OvQuaternion&	Quaternion::GetQuaternion()
{
	return m_value;
}
//////////////////////////////////////////////////////////////////////////


//////////////////////////////////////////////////////////////////////////
void			Integer::FromString( const OvString& expData )
{
	sscanf_s( expData.c_str(), "%d", &m_value );
}
OvString			Integer::ToString()
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
void			String::FromString( const OvString& expData )
{
	m_value = expData;
}
OvString			String::ToString()
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
void			ObjectID::FromString( const OvString& expData )
{
	OvObjectID::id_core_type core_id;
	sscanf_s( expData.c_str(), "%d", &core_id );
	m_value = OvObjectID( core_id );
}
OvString			ObjectID::ToString()
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

void OliveValue::UserData::FromString( const OvString& expData )
{
	sscanf_s( expData.c_str(), "%p", &m_value );
}

OvString OliveValue::UserData::ToString()
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