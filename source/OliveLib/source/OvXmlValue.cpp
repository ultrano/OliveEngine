#include "OvXmlValue.h"

OvXmlValue::OvXmlValue()
//: m_slidingElement( NULL )
{

}

OvXmlValue::~OvXmlValue()
{

}
OvXmlValue*  OvXmlValue::m( const std::string& child_value )
{
	child_element_table::iterator itor = m_childElements.find( child_value );
	if ( itor != m_childElements.end() )
	{
		return itor->second;
	}
 	return NULL;
}


std::string& OvXmlValue::Text()
{
	return m_text;
}

bool OvXmlValue::Attribute( std::string& attribute_name, std::string& attribute_value )
{
	attribute_table::iterator itor = m_attributes.find( attribute_name );
	if ( itor != m_attributes.end() )
	{
		attribute_value =itor->second;
		return true;
	}
	return false;
}

void OvXmlValue::SetText( std::string& text )
{
	m_text = text;
}

void OvXmlValue::SetAttribute( std::string& attribute_name, std::string& attribute_value )
{
	m_attributes[ attribute_name ] = attribute_value;
}

OvXmlValue* OvXmlValue::Sliding()
{
	return m_slidingElement;
}

void OvXmlValue::SetSliding( OvXmlValue* sliding_element )
{
	m_slidingElement = sliding_element;
}

void OvXmlValue::InsertChild( std::string& elem_value, OvXmlValue* child )
{
	OvXmlValue* same_child = NULL;
	child_element_table::iterator itor = m_childElements.find( elem_value );
	if ( itor != m_childElements.end() )
	{
		same_child = itor->second;
	}
	if ( same_child )
	{
		same_child->SetSliding( child );
	}
	else
	{
		m_childElements[ elem_value ] = child;
	}
}