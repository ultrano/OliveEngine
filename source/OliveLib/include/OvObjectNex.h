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

	//! Object Name
	void			SetName(const OvChar* _pName);
	const OvString&	GetName();

private:

	OvString				m_name;

};