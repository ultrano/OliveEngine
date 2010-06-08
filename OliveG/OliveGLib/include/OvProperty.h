#pragma once
#include <string>
#include "OvRTTI.h"
#include "OvMemObject.h"

class OvObject;
class OvObjectProperties;
class OvProperty : public OvMemObject
{
	OvRTTI_DECL(OvProperty);
public:

	OvProperty(){};
	virtual ~OvProperty(){};

	virtual bool	Extract(OvObject* pObj, OvObjectProperties& rXml) = 0;
	virtual bool	Inject(OvObject* pObj, OvObjectProperties& rXml) = 0;

	void*			Access(OvObject* pObj);
	unsigned int	GetOffset();
	void			SetOffset(unsigned int uiOffset);

	std::string&	GetPropertyName();
	void			SetPropertyName(const std::string& strPropName);

private:

	std::string		m_strPropertyName;
	unsigned int	m_uiOffset;

};