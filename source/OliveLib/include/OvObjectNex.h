#pragma once
#include "OvObject.h"

namespace OliveValue{ OvREF_POINTER(Value); };
//! Object Nexus Layer
OvREF_POINTER(OvObjectNex);
class OvObjectNex : public OvObject
{
	OvRTTI_DECL( OvObjectNex );
	OvPROPERTY_BAG_DECL(OvObjectNex);
public:

	void	SetExtraProperty( OliveValue::ValueSPtr val );
	OliveValue::ValueSPtr GetExtraProperty( const OvString& key );

	//! Object Name
	void			SetName(const OvChar* _pName);
	const OvString&	GetName();

private:

	OliveValue::ValueSPtr	m_extra;
	OvString				m_name;

};