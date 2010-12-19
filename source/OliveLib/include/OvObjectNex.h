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

	//!< Extra Property가 여러개 셋팅 되는 구조에서 
	//!< 한게만 받는 형태로 변경 됐다.
	//!< 만일 여러개가 필요한경우 Table로 지정해 사용하면 된다.
	void	SetExtraProperty( OliveValue::ValueSPtr val );
	OliveValue::ValueSPtr GetExtraProperty( const OvString& key );

	//! Object Name
	void			SetName(const OvChar* _pName);
	const OvString&	GetName();

private:

	OliveValue::ValueSPtr	m_extra;
	OvString				m_name;

};