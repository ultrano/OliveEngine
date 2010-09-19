 #pragma once
#include "OvMemObject.h"
#include <string>
#include <map>

class OvXmlValue : public OvMemObject
{
	typedef std::map<std::string,std::string> attribute_table;
	typedef std::map<std::string,OvXmlValue*> child_element_table;
public:

	OvXmlValue();
	~OvXmlValue();

	OvXmlValue* m( const std::string& child_value );

	std::string&	Text();
	bool			Attribute( std::string& attribute_name, std::string& attribute_value );
	OvXmlValue*		Sliding();

	void			SetText( std::string& text );
	void			SetAttribute( std::string& attribute_name, std::string& attribute_value );
	void			SetSliding( OvXmlValue* sliding_element );

	void			InsertChild( std::string& elem_value, OvXmlValue* child );

private:

	std::string m_text;
	attribute_table m_attributes;
	child_element_table m_childElements;
	OvXmlValue*	m_slidingElement;

};