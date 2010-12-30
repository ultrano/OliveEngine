#pragma once
#include "OvObject.h"
#include "OliveValue.h"
//! Object Nexus Layer
OvREF_POINTER(OvObjectNex);
class OvObjectNex : public OvObject
{
	OvRTTI_DECL( OvObjectNex );
	OvPROPERTY_BAG_DECL(OvObjectNex);
public:

	void	AddPrivateProperty( const OvString& key, OliveValue::Value& val );
	OliveValue::ValueSPtr GetPrivateProperty( const OvString& key );

	//! Object Name
	void			SetName(const OvChar* _pName);
	const OvString&	GetName();

private:

	OliveValue::Table		m_prop_table;
	OvString				m_name;

};