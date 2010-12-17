#include "OvTuple.h"
OvRTTI_IMPL(Table)

void OliveValue::Table::FromString( const OvString& expData )
{

}

OvString OliveValue::Table::ToString()
{
	OvString tostr;
	tostr = OvFormatString( "!%d", Size() );
	value_table::iterator itor = m_table.begin();
	for( ; itor != m_table.end() ; ++itor )
	{
		ValueSPtr val = itor->second;

		const OvString& type	= OvTypeName( val );
		const OvString& key		= itor->first;
		OvString		valstr	= val->ToString();

		tostr += OvFormatString( "[%d-%d-%d]%s"
							   , type.size()
							   , key.size()
							   , valstr.size()
							   , (type+key+valstr).c_str() );
	}
}

void OliveValue::Table::Insert( const OvString& key, ValueSPtr val )
{
	m_table[ key ] = val;
}

OliveValue::ValueSPtr OliveValue::Table::Find( const OvString& key )
{
	value_table::iterator itor = m_table.find( key );
	if ( itor == m_table.end() )
	{
		return itor->second;
	}
	return NULL;
}

OvUInt OliveValue::Table::Size()
{
	return m_table.size();
}