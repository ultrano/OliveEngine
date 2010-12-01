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

	virtual bool	Extract(OvObject* pObj, OvObjectProperties& rXml) = 0;
	virtual bool	Inject(OvObject* pObj, OvObjectProperties& rXml) = 0;

	void*			Access(OvObject* pObj);
	unsigned int	GetOffset();
	void			SetOffset(unsigned int uiOffset);

	OvString&	GetPropertyName();
	void			SetPropertyName(const OvString& strPropName);

private:

	OvString		m_strPropertyName;
	unsigned int	m_uiOffset;

};