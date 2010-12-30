#include "OliveValue.h"
#include "OvStringUtility.h"

using namespace OliveValue;
//////////////////////////////////////////////////////////////////////////
//////////////////////////////////////////////////////////////////////////
//////////////////////////////////////////////////////////////////////////

/// Ovint
template<> 
OvInt			OliveValue::FromString( const OvString& str )
{
	OvInt ret;
	sscanf_s( str.c_str(), "%d", &ret );
	return ret;
}

template<> 
OvString		OliveValue::ToString( const OvInt& val )
{
	return OvString( OvFormatString( "%d", val ) );
}

/// OvUInt
template<> 
OvUInt			OliveValue::FromString( const OvString& str )
{
	OvUInt ret;
	sscanf_s( str.c_str(), "%d", &ret );
	return ret;
}

template<> 
OvString		OliveValue::ToString( const OvUInt& val )
{
	return OvString( OvFormatString( "%d", val ) );
}

/// OvBool
template<>
OvBool			OliveValue::FromString( const OvString& str )
{
	if ( _stricmp( "0",str.c_str() ) == 0 || _stricmp( "false",str.c_str() ) == 0 )
	{
		return false;
	}
	else if ( _stricmp( "1",str.c_str() ) == 0 || _stricmp( "true",str.c_str() ) == 0 )
	{
		return true;
	}
	OvAssert(false);
	return false;
}

template<>
OvString		OliveValue::ToString( const OvBool& val )
{
	return OvString( OvFormatString( "%d", val ) );
}

/// OvFloat
//////////////////////////////////////////////////////////////////////////
template<>
OvFloat			OliveValue::FromString( const OvString& str )
{
	OvFloat ret;
	sscanf_s( str.c_str(), "%f", &ret );
	return ret;
}

template<>
OvString			OliveValue::ToString( const OvFloat& val )
{
	return OvString( OvFormatString( "%f", val ) );
}

/// OvPoint2
//////////////////////////////////////////////////////////////////////////
template<>
OvPoint2			OliveValue::FromString( const OvString& str )
{
	OvPoint2 ret;
	sscanf_s( str.c_str(), "%f,%f", &ret.x, &ret.y );
	return ret;
}

template<>
OvString			OliveValue::ToString( const OvPoint2& val )
{
	return OvString( OvFormatString( "%f,%f", val.x, val.y ) );
}

/// OvPoint3
//////////////////////////////////////////////////////////////////////////

template<>
OvPoint3			OliveValue::FromString( const OvString& str )
{
	OvPoint3 ret;
	sscanf_s( str.c_str(), "%f,%f,%f", &ret.x, &ret.y, &ret.z );
	return ret;
}

template<>
OvString			OliveValue::ToString( const OvPoint3& val )
{
	return OvString( OvFormatString( "%f,%f,%f", val.x, val.y, val.z ) );
}

/// OvQuaternion
//////////////////////////////////////////////////////////////////////////

template<>
OvQuaternion		OliveValue::FromString( const OvString& str )
{
	OvQuaternion ret;
	sscanf_s( str.c_str(), "%f,%f,%f,%f", &ret.x, &ret.y, &ret.z, &ret.w );
	return ret;
}

template<>
OvString			OliveValue::ToString( const OvQuaternion& val )
{
	return OvString( OvFormatString( "%f,%f,%f,%f", val.x, val.y, val.z, val.w ) );
}

///OvObjectID
//////////////////////////////////////////////////////////////////////////

template<>
OvObjectID				OliveValue::FromString( const OvString& str )
{
	OvObjectID::id_core_type core_id;
	sscanf_s( str.c_str(), "%d", &core_id );
	return OvObjectID( core_id );
}

template<>
OvString			OliveValue::ToString( const OvObjectID& val )
{
	return OvString( OvFormatString( "%d", val ) );
}

/// OvColor
//////////////////////////////////////////////////////////////////////////

template<>
OvColor				OliveValue::FromString( const OvString& expData )
{
	//!< 읽어오는 형식은 %d에 의해 숫자형으로 써져있기 때문에 숫자형인 OvInt나 OvUInt 로 받아야한다.
	//!< OvColor::a r g b 멤버로 바로 받으면 가장 마지막인 b를 받는순간 arg는 b의 4바이트읽기에 의해 덮여 쓰여지게 된다.
	//!< 그렇다고 char a,r,g,b; 로 받으면 스택 오버플로우로 함수가 무너진게 된다.
	OvColor ret;
	OvUInt a,r,g,b;
	sscanf_s( expData.c_str(), "a%dr%dg%db%d", &a, &r, &g, &b );

	return OvColor(a,r,g,b);
}

template<>
OvString			OliveValue::ToString( const OvColor& val )
{
	return OvString(OvFormatString( "a%dr%dg%db%d", val.a, val.r, val.g, val.b ));
}
//////////////////////////////////////////////////////////////////////////
//////////////////////////////////////////////////////////////////////////
//////////////////////////////////////////////////////////////////////////
OvRTTI_IMPL(Value);
VALUE_TYPE_IMPL(OvInt);
VALUE_TYPE_IMPL(OvUInt);
VALUE_TYPE_IMPL(OvBool);
VALUE_TYPE_IMPL(OvFloat);
VALUE_TYPE_IMPL(OvPoint2);
VALUE_TYPE_IMPL(OvPoint3);
VALUE_TYPE_IMPL(OvQuaternion);
VALUE_TYPE_IMPL(OvObjectID);
VALUE_TYPE_IMPL(OvColor);