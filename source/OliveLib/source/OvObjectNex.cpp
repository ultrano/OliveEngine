#include "OvObjectNex.h"
#include "OliveValue.h"
#include "OvRegisterableProperties.h"
OvRTTI_IMPL( OvObjectNex );

OvPROPERTY_BAG_BEGIN(OvObjectNex);
OvPROPERTY_BAG_REGISTER( OvPropAccesser_STL_string, m_name );
	OvPROPERTY_BAG_REGISTER( OvPropAccesser_olive_value, m_extra );
OvPROPERTY_BAG_END(OvObjectNex);

void	OvObjectNex::SetName( const OvChar* name )
{
	m_name = name;
}
const OvString& OvObjectNex::GetName()
{
	return m_name;
}

void OvObjectNex::SetExtraProperty( OliveValue::ValueSPtr val )
{
	m_extra = val;
}

OliveValue::ValueSPtr OvObjectNex::GetExtraProperty( const OvString& key )
{
	return m_extra;
}