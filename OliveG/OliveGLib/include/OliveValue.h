#pragma once
#include "OvMemObject.h"
#include "OvUtility_RTTI.h"
#include "OvPoint2.h"
#include "OvPoint3.h"
#include "OvQuaternion.h"
#include "OvObjectID.h"

namespace OliveValue
{

#define	ACCEPT_STRING_CONSTRUCTOR	public:__this_class(){};__this_class(const string& strValue){SetValue(strValue);};

	class Value : public OvMemObject
	{
		friend class OvObject;
		OvRTTI_DECL_ROOT(Value);
		virtual ~Value();
	public:
		Value();
	public:
		virtual void	SetValue( const string& expData ) = 0;
		virtual string	GetValue() = 0;
	};

	class Float : public OliveValue::Value
	{
		OvRTTI_DECL(Float);
		ACCEPT_STRING_CONSTRUCTOR
	public:
		virtual void	SetValue( const string& expData );
		virtual string	GetValue();
	public:
		void			SetFloat( float expValue );
		float			GetFloat();
	private:
		float	m_value;
	};
	
	class Point2 : public OliveValue::Value
	{
		OvRTTI_DECL(Point2);
		ACCEPT_STRING_CONSTRUCTOR
	public:
		virtual void	SetValue( const string& expData );
		virtual string	GetValue();
	public:
		void			SetPoint2( const OvPoint2& expValue );
		void			SetPoint2( float x, float y );
		const OvPoint2&	GetPoint2();
	private:
		OvPoint2	m_value;
	};

	class Point3 : public OliveValue::Value
	{
		OvRTTI_DECL(Point3);
		ACCEPT_STRING_CONSTRUCTOR
	public:
		virtual void	SetValue( const string& expData );
		virtual string	GetValue();
	public:
		void			SetPoint3( const OvPoint3& expValue );
		void			SetPoint3( float x, float y, float z );
		const OvPoint3&	GetPoint3();
	private:
		OvPoint3	m_value;
	};

	class Quaternion : public OliveValue::Value
	{
		OvRTTI_DECL(Quaternion);
		ACCEPT_STRING_CONSTRUCTOR
	public:
		virtual void	SetValue( const string& expData );
		virtual string	GetValue();
	public:
		void			  SetQuaternion( const OvQuaternion& expValue );
		void			  SetQuaternion( float x, float y, float z, float w );
		const OvQuaternion& GetQuaternion();
	private:
		OvQuaternion	m_value;
	};

	class Integer : public OliveValue::Value
	{
		OvRTTI_DECL(Integer);
		ACCEPT_STRING_CONSTRUCTOR
	public:
		virtual void	SetValue( const string& expData );
		virtual string	GetValue();
	public:
		void			SetInteger( int expValue );
		int				GetInteger();
	private:
		int		m_value;
	};

	class String : public OliveValue::Value
	{
		OvRTTI_DECL(String);
		ACCEPT_STRING_CONSTRUCTOR
	public:
		virtual void	SetValue( const string& expData );
		virtual string	GetValue();
	public:
		void			SetString( const string& expValue );
		string			GetString();
	private:
		string		m_value;
	};

	class ObjectID : public OliveValue::Value
	{
		OvRTTI_DECL(ObjectID);
		ACCEPT_STRING_CONSTRUCTOR
	public:
		virtual void	SetValue( const string& expData );
		virtual string	GetValue();
	public:
		void			SetObjectID( const OvObjectID& expValue );
		const OvObjectID&	GetObjectID();
	private:
		OvObjectID		m_value;
	};

	Value*	ValueFactory(const std::string& valueType);

}
