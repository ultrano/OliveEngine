#include "OvObjectNex.h"
#include "OliveValue.h"
OvRTTI_IMPL( OvObjectNex );

void	OvObjectNex::SetName( const OvChar* name )
{
	m_name = name;
}
const OvString& OvObjectNex::GetName()
{
	return m_name;
}