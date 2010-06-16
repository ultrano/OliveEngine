#pragma once
#include "OvMemObject.h"
#include "OvUtility_RTTI.h"
#include "OvRTTFactory.h"
#include <string>

namespace OvExtraProperty
{
	class Value : public OvMemObject
	{
		OvRTTI_DECL_ROOT(Value);
	public:
		Value();
		virtual ~Value();
	public:
		virtual void	SetValue( const string& expData ) = 0;
		virtual string	GetValue() = 0;
	};

	class Float : public OvExtraProperty::Value
	{
		OvRTTI_DECL(Float);
		OvRTTF_CONSTRUCTOR_DECL(Float);
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

	class Integer : public OvExtraProperty::Value
	{
		OvRTTI_DECL(Integer);
		OvRTTF_CONSTRUCTOR_DECL(Integer);
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

	class String : public OvExtraProperty::Value
	{
		OvRTTI_DECL(String);
		OvRTTF_CONSTRUCTOR_DECL(String);
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


}