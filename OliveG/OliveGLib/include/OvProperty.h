#pragma once
#include <string>

class OvObject;
class TiXmlElement;
class OvProperty
{
public:

	virtual bool	Store(OvObject* pObj, TiXmlElement& rXml) = 0;
	virtual bool	Restore(OvObject* pObj, TiXmlElement& rXml) = 0;

	void*			Access(OvObject* pObj);
	unsigned int	GetOffset();
	void			SetOffset(unsigned int uiOffset);

	std::string&			GetPropertyName();
	void			SetPropertyName(const std::string& strPropName);

private:

	std::string			m_strPropertyName;
	unsigned int	m_uiOffset;

};
#define OvPROP_PROTECT_DECL class OvPropProtector;\
	OvAutoPtr<OvPropProtector> m_pProtector;