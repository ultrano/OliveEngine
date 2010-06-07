#pragma once
#include <string>
#include "OvRTTI.h"

class OvObject;
class OvObjectStore;
class OvProperty
{
	OvRTTI_DECL(OvProperty);
public:

	OvProperty(){};
	virtual ~OvProperty(){};

	virtual bool	Extract(OvObject* pObj, OvObjectStore& rXml) = 0;
	virtual bool	Inject(OvObject* pObj, OvObjectStore& rXml) = 0;

	void*			Access(OvObject* pObj);
	unsigned int	GetOffset();
	void			SetOffset(unsigned int uiOffset);

	std::string&	GetPropertyName();
	void			SetPropertyName(const std::string& strPropName);

private:

	std::string		m_strPropertyName;
	unsigned int	m_uiOffset;

};