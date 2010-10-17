#pragma once
#include "OvMemObject.h"
#include "OvUtility_RTTI.h"
#include "OvPoint2.h"
#include "OvPoint3.h"
#include "OvQuaternion.h"
#include "OvObjectID.h"

namespace OliveValue
{

// 유틸리티 매크로, 자주 쓰이는 몇몇 생성자와 함수형태,멤버 형태를 지정한다.
#define	OLIVE_VALUE_TYPE( type_name )	\
	private:type_name m_value;\
	public:\
	__this_class(){};\
	__this_class( const char* strValue ){SetValue( string( strValue ) );};\
	__this_class( string& strValue ){SetValue(strValue);};\
	__this_class( const type_name& typeValue ){m_value = typeValue;};\
	const __this_class& operator=( const type_name& typeValue ){ m_value = typeValue; return *this; };\
	operator const type_name& (){ return m_value; };


	class Value;
	Value*	Factory(const std::string& valueType);
	template<typename Type_0>
	Type_0*	Factory()
	{
		OvRTTI* rtti = const_cast<OvRTTI*>(Type_0::GetRTTI());
		if ( rtti )
		{
			return (Type_0*) Factory( rtti->TypeName() );
		}
		return NULL;
	};

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

	class Bool : public OliveValue::Value
	{
		OvRTTI_DECL(Bool);
		OLIVE_VALUE_TYPE(bool);
	public:
		virtual void	SetValue( const string& expData );
		virtual string	GetValue();
	public:
		void			SetBool( bool expData );
		bool			GetBool();

	};
	class Float : public OliveValue::Value
	{
		OvRTTI_DECL(Float);
		OLIVE_VALUE_TYPE(float);
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
		OLIVE_VALUE_TYPE(OvPoint2);
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
		OLIVE_VALUE_TYPE(OvPoint3);
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
		OLIVE_VALUE_TYPE(OvQuaternion);
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
		OLIVE_VALUE_TYPE(int);
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
		OLIVE_VALUE_TYPE(string);
	public:
		virtual void	SetValue( const string& expData );
		virtual string	GetValue();
	public:
		void			SetString( const string& expValue );
		const string&	GetString();
	};

	class ObjectID : public OliveValue::Value
	{
		OvRTTI_DECL(ObjectID);
		OLIVE_VALUE_TYPE(OvObjectID);
	public:
		virtual void	SetValue( const string& expData );
		virtual string	GetValue();
	public:
		void			SetObjectID( const OvObjectID& expValue );
		const OvObjectID&	GetObjectID();
	};

// 	class ValueTuple : public OliveValue::Value
// 	{
// 
// 	};

}
