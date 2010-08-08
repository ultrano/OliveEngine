#pragma once
#include "OvMemObject.h"
#include "OvUtility_RTTI.h"
#include "OvPoint2.h"
#include "OvPoint3.h"
#include "OvQuaternion.h"
#include "OvObjectID.h"

namespace OliveValue
{

#define	ACCEPT_STRING_CONSTRUCTOR( type_name )	\
	private:type_name m_value;\
	public:\
	__this_class(){};\
	__this_class( const char* strValue ){SetValue( string( strValue ) );};\
	__this_class( string& strValue ){SetValue(strValue);};\
	__this_class( const type_name& typeValue ){m_value = typeValue;};

	class Value;
	Value*	Factory(const std::string& valueType);

	class Value : public OvMemObject
	{
		friend Value*	Factory(const std::string& valueType);
		friend class OvObject;
		OvRTTI_DECL_ROOT(Value);
		Value();
		virtual ~Value();
	public:
		virtual void	SetValue( const string& expData ) = 0;
		virtual string	GetValue() = 0;
	};

	class Float : public OliveValue::Value
	{
		OvRTTI_DECL(Float);
		ACCEPT_STRING_CONSTRUCTOR(float);
	public:
		virtual void	SetValue( const string& expData );
		virtual string	GetValue();
	public:
		void			SetFloat( float expValue );
		float			GetFloat();
	};
	
	class Point2 : public OliveValue::Value
	{
		OvRTTI_DECL(Point2);
		ACCEPT_STRING_CONSTRUCTOR(OvPoint2);
	public:
		virtual void	SetValue( const string& expData );
		virtual string	GetValue();
	public:
		void			SetPoint2( const OvPoint2& expValue );
		void			SetPoint2( float x, float y );
		const OvPoint2&	GetPoint2();
	};

	class Point3 : public OliveValue::Value
	{
		OvRTTI_DECL(Point3);
		ACCEPT_STRING_CONSTRUCTOR(OvPoint3);
	public:
		virtual void	SetValue( const string& expData );
		virtual string	GetValue();
	public:
		void			SetPoint3( const OvPoint3& expValue );
		void			SetPoint3( float x, float y, float z );
		const OvPoint3&	GetPoint3();
	};

	class Quaternion : public OliveValue::Value
	{
		OvRTTI_DECL(Quaternion);
		ACCEPT_STRING_CONSTRUCTOR(OvQuaternion);
	public:
		virtual void	SetValue( const string& expData );
		virtual string	GetValue();
	public:
		void			  SetQuaternion( const OvQuaternion& expValue );
		void			  SetQuaternion( float x, float y, float z, float w );
		const OvQuaternion& GetQuaternion();
	};

	class Integer : public OliveValue::Value
	{
		OvRTTI_DECL(Integer);
		ACCEPT_STRING_CONSTRUCTOR(int);
	public:
		virtual void	SetValue( const string& expData );
		virtual string	GetValue();
	public:
		void			SetInteger( int expValue );
		int				GetInteger();
	};

	class String : public OliveValue::Value
	{
		OvRTTI_DECL(String);
		ACCEPT_STRING_CONSTRUCTOR(string);
	public:
		virtual void	SetValue( const string& expData );
		virtual string	GetValue();
	public:
		void			SetString( const string& expValue );
		string			GetString();
	};

	class ObjectID : public OliveValue::Value
	{
		OvRTTI_DECL(ObjectID);
		ACCEPT_STRING_CONSTRUCTOR(OvObjectID);
	public:
		virtual void	SetValue( const string& expData );
		virtual string	GetValue();
	public:
		void			SetObjectID( const OvObjectID& expValue );
		const OvObjectID&	GetObjectID();
	};

}
