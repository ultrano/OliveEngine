#pragma once
#include "OliveValue.h"
#include <map>

namespace OliveValue
{
	class Table : public OliveValue::Value
	{
		OvRTTI_DECL(Table);
		typedef std::map<OvString,ValueSPtr> value_table;
	public:
		virtual void		FromString( const OvString& expData ) override;
		virtual OvString	ToString() override;
	public:
		void				Insert( const OvString& key, ValueSPtr val );
		ValueSPtr			Find( const OvString& key );

		OvUInt				Size();
	private:
		 value_table m_table;
	};
}