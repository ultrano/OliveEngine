#pragma once
#include "OvTypeDef.h"
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
	__this_class( const char* strValue ){FromString( OvString( strValue ) );};\
	__this_class( OvString& strValue ){FromString(strValue);};\
	__this_class( const type_name& typeValue ){m_value = typeValue;};\
	const __this_class& operator=( const type_name& typeValue ){ m_value = typeValue; return *this; };\
	operator const type_name& (){ return m_value; };


	class Value;
	Value*	Factory(const OvString& valueType);
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
		friend Value*	Factory(const OvString& valueType);
		friend class OvObject;
		OvRTTI_DECL_ROOT(Value);
		Value();
		virtual ~Value();
	public:
		void			FromString( const char* expData );
		virtual void	FromString( const OvString& expData ) = 0;
		virtual OvString	ToString() = 0;
	};

	class Bool : public OliveValue::Value
	{
		OvRTTI_DECL(Bool);
		OLIVE_VALUE_TYPE(OvBool);
	public:
		virtual void	FromString( const OvString& expData );
		virtual OvString	ToString();
	public:
		void			SetBool( OvBool expData );
		OvBool			GetBool();

	};
	class Float : public OliveValue::Value
	{
		OvRTTI_DECL(Float);
		OLIVE_VALUE_TYPE(OvFloat);
	public:
		virtual void	FromString( const OvString& expData );
		virtual OvString	ToString();
	public:
		void			SetFloat( OvFloat expValue );
		OvFloat			GetFloat();
	};
	
	class Point2 : public OliveValue::Value
	{
		OvRTTI_DECL(Point2);
		OLIVE_VALUE_TYPE(OvPoint2);
	public:
		virtual void	FromString( const OvString& expData );
		virtual OvString	ToString();
	public:
		void			SetPoint2( const OvPoint2& expValue );
		void			SetPoint2( OvFloat x, OvFloat y );
		const OvPoint2&	GetPoint2();
	};

	class Point3 : public OliveValue::Value
	{
		OvRTTI_DECL(Point3);
		OLIVE_VALUE_TYPE(OvPoint3);
	public:
		virtual void	FromString( const OvString& expData );
		virtual OvString	ToString();
	public:
		void			SetPoint3( const OvPoint3& expValue );
		void			SetPoint3( OvFloat x, OvFloat y, OvFloat z );
		const OvPoint3&	GetPoint3();
	};

	class Quaternion : public OliveValue::Value
	{
		OvRTTI_DECL(Quaternion);
		OLIVE_VALUE_TYPE(OvQuaternion);
	public:
		virtual void	FromString( const OvString& expData );
		virtual OvString	ToString();
	public:
		void			  SetQuaternion( const OvQuaternion& expValue );
		void			  SetQuaternion( OvFloat x, OvFloat y, OvFloat z, OvFloat w );
		const OvQuaternion& GetQuaternion();
	};

	class Integer : public OliveValue::Value
	{
		OvRTTI_DECL(Integer);
		OLIVE_VALUE_TYPE(OvInt);
	public:
		virtual void	FromString( const OvString& expData );
		virtual OvString	ToString();
	public:
		void			SetInteger( OvInt expValue );
		OvInt				GetInteger();
	};

	class String : public OliveValue::Value
	{
		OvRTTI_DECL(String);
		OLIVE_VALUE_TYPE(OvString);
	public:
		virtual void	FromString( const OvString& expData );
		virtual OvString	ToString();
	public:
		void			SetString( const OvString& expValue );
		const OvString&	GetString();
	};

	class ObjectID : public OliveValue::Value
	{
		OvRTTI_DECL(ObjectID);
		OLIVE_VALUE_TYPE(OvObjectID);
	public:
		virtual void	FromString( const OvString& expData );
		virtual OvString	ToString();
	public:
		void			SetObjectID( const OvObjectID& expValue );
		const OvObjectID&	GetObjectID();
	};

	class UserData : public OliveValue::Value
	{
		typedef void* void_pointer;
		OvRTTI_DECL(UserData);
		OLIVE_VALUE_TYPE(void_pointer);
	public:
		virtual void	FromString( const OvString& expData );
		virtual OvString	ToString();
	public:
		void			SetUserData( void* userData );
		void*			GetUserData();
	};

// 	class ValueTuple : public OliveValue::Value
// 	{
// 
// 	};

}
