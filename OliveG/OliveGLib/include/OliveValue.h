#pragma once
#include "OvMemObject.h"
#include "OvUtility_RTTI.h"

namespace OliveValue
{

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
	public:
		Float(){};
		virtual void	SetValue( const string& expData );
		virtual string	GetValue();
	public:
		void			SetFloat( float expValue );
		float			GetFloat();
	private:
		float	m_value;
	};

	class Integer : public OliveValue::Value
	{
		OvRTTI_DECL(Integer);
	public:
		Integer(){};
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
	public:
		String(){};
		virtual void	SetValue( const string& expData );
		virtual string	GetValue();
	public:
		void			SetString( const string& expValue );
		string			GetString();
	private:
		string		m_value;
	};

	Value*	ValueFactory(const std::string& valueType);


#define REGIST_VALUE_TYPE_BEGINE OliveValue::Value*	OliveValue::ValueFactory(const std::string& valueType){\
	if( valueType.empty() ){return NULL;}
#define	REGIST_VALUE_TYPE( classname ) else if( std::string(#classname) == valueType){return new classname();}
#define REGIST_VALUE_TYPE_END	return NULL;};
}
