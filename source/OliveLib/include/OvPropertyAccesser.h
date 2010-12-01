#pragma once
#include "OvTypeDef.h"
#include "OvUtility_RTTI.h"
#include "OvMemObject.h"

#define PROPACCESSER( prop_type ) OvPropAccesser_##prop_type

class OvObject;
class OvObjectProperties;
class OvPropertyAccesser
{
	OvRTTI_DECL_ROOT(OvPropertyAccesser);
public:

	OvPropertyAccesser();
	virtual ~OvPropertyAccesser();

	virtual OvBool	Extract(OvObject* pObj, OvObjectProperties& rXml) = 0;
	virtual OvBool	Inject(OvObject* pObj, OvObjectProperties& rXml) = 0;

	void*			Access(OvObject* pObj);
	OvUInt	GetOffset();
	void			SetOffset(OvUInt uiOffset);

	OvString&	GetPropertyName();
	void			SetPropertyName(const OvString& strPropName);

private:

	OvString		m_strPropertyName;
	OvUInt	m_uiOffset;

};