#include "OvPropertyBag.h"
#include "OvPropertyAccesser.h"

OvPropertyBag::OvPropertyBag()
{

}

OvPropertyBag::~OvPropertyBag()
{
}

unsigned OvPropertyBag::GetPropertiesCount()
{
	return (unsigned)m_properties.size();
}

OvPropertyAccesser* OvPropertyBag::GetPropertyAt( unsigned index )
{
	if ( index < m_properties.size() )
	{
		return m_properties.at( index ).GetRear();
	}
	return NULL;
}

OvPropertyAccesser* OvPropertyBag::FindProperty( const std::string& name )
{
	OvPropertyAccesser* accesser = NULL;
	for ( unsigned i = 0 ; accesser = GetPropertyAt( i ) ; ++i )
	{
		if ( accesser->GetPropertyName() == name )
		{
			return accesser;
		}
	}
	return NULL;
}

void				OvPropertyBag::AddProperty( OvPropertyAccesser* pProperty )
{
	m_properties.push_back( pProperty );
}