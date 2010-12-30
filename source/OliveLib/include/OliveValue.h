#pragma once
#include "OvTypeDef.h"
#include "OvRefBase.h"
#include "OvUtility_RTTI.h"
#include "OvPoint2.h"
#include "OvPoint3.h"
#include "OvQuaternion.h"
#include "OvObjectID.h"
#include "OvColor.h"
#include <map>
class OvInputStream;
class OvOutputStream;
namespace OliveValue
{
// 유틸리티 매크로, 자주 쓰이는 몇몇 생성자와 함수형태,멤버 형태를 지정한다.
#define	OLIVE_VALUE_TYPE( type_name )	\
	private:type_name m_value;\
	public:\
	__this_class(){};\
	__this_class( const OvChar* strValue ){FromString( OvString( strValue ) );};\
	__this_class( OvString& strValue ){FromString(strValue);};\
	__this_class( const type_name& typeValue ){m_value = typeValue;};\
	const __this_class& operator=( const type_name& typeValue ){ m_value = typeValue; return *this; };\
	operator const type_name& (){ return m_value; };

	//////////////////////////////////////////////////////////////////////////

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

	//////////////////////////////////////////////////////////////////////////

	OvREF_POINTER(Value);
	class Value : public OvRefBase
	{
		friend Value*	Factory(const OvString& valueType);
		friend class OvObject;
		OvRTTI_DECL_ROOT(Value);
		Value();
		virtual ~Value();
	public:
		void				FromString( const OvChar* expData );
		virtual void		FromString( const OvString& expData ) = 0;
		virtual OvString	ToString() = 0;
	/*public:
		void				FromStream( OvOutputStream& stream );
		void				ToStream( OvInputStream& stream );*/
	public:
		//!< 기본 복사함수 구현, 오버헤드가 심할수 있는 방법이지만 공통된 방법이므로 기본적으로 제공.
		virtual void	CopyFrom( Value& val ) { FromString( val.ToString() ); };
	};

	//////////////////////////////////////////////////////////////////////////

	OvREF_POINTER(Bool);
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

	//////////////////////////////////////////////////////////////////////////

	OvREF_POINTER(Float);
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

	//////////////////////////////////////////////////////////////////////////

	OvREF_POINTER(Point2);
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

	//////////////////////////////////////////////////////////////////////////

	OvREF_POINTER(Point3);
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

	//////////////////////////////////////////////////////////////////////////

	OvREF_POINTER(Quaternion);
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

	//////////////////////////////////////////////////////////////////////////

	OvREF_POINTER(Integer);
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

	//////////////////////////////////////////////////////////////////////////

	OvREF_POINTER(String);
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

	//////////////////////////////////////////////////////////////////////////

	OvREF_POINTER(ObjectID);
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
	
	//////////////////////////////////////////////////////////////////////////

	OvREF_POINTER(UserData);
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

	//////////////////////////////////////////////////////////////////////////

	OvREF_POINTER(Color);
	class Color : public OliveValue::Value
	{
		OvRTTI_DECL(Color);
		OLIVE_VALUE_TYPE(OvColor);
	public:
		virtual void	FromString( const OvString& expData );
		virtual OvString	ToString();
	public:
		void			SetColor( const OvColor& userData );
		const OvColor&		GetColor();
	};

	//////////////////////////////////////////////////////////////////////////

	OvREF_POINTER(Table);
	class Table : public OliveValue::Value
	{
		OvRTTI_DECL(Table);
		typedef std::map<OvString,ValueSPtr> value_table;
	public:
		virtual void		FromString( const OvString& expData ) override;
		virtual OvString	ToString() override;
	public:
		void				Insert( const OvString& key, ValueSPtr val );
		void				Insert( const OvString& key, Value& val );

		void				Merge( TableSPtr table );
		
		ValueSPtr			Remove( const OvString& key );

		template<typename T>
		OvSmartPointer<T>	Find( const OvString& key );
		ValueSPtr			Find( const OvString& key );
		
		void				Clear();

		OvUInt				Size();
	private:
		value_table m_table;
	};

	template<typename T>
	OvSmartPointer<T> OliveValue::Table::Find( const OvString& key )
	{
		return OvCastTo<T>( Find(key) );
	}
}
namespace Ov = OliveValue;
namespace OliveValue
{
	template<typename T>
	T		FromString( const OvString& str );
	template<typename T>
	OvString ToString( const T& val );

	/// Ovint
	template<>
	OvInt	FromString( const OvString& str );
	template<>
	OvString ToString( const OvInt& val );

	/// OvUInt
	template<>
	OvUInt	FromString( const OvString& str );
	template<>
	OvString ToString( const OvUInt& val );

	/// OvBool
	template<>
	OvBool	FromString( const OvString& str );
	template<>
	OvString ToString( const OvBool& val );

	/// OvFloat
	template<>
	OvFloat	FromString( const OvString& str );
	template<>
	OvString ToString( const OvFloat& val );

	/// OvPoint2
	template<>
	OvPoint2	FromString( const OvString& str );
	template<>
	OvString	ToString( const OvPoint2& val );

	/// OvPoint3
	template<>
	OvPoint3	FromString( const OvString& str );
	template<>
	OvString	ToString( const OvPoint3& val );

	/// OvQuaternion
	template<>
	OvQuaternion FromString( const OvString& str );
	template<>
	OvString	ToString( const OvQuaternion& val );

	/// OvObjectID
	template<>
	OvObjectID	FromString( const OvString& str );
	template<>
	OvString	ToString( const OvObjectID& val );

	/// OvColor
	template<>
	OvColor		FromString( const OvString& str );
	template<>
	OvString	ToString( const OvColor& val );
}