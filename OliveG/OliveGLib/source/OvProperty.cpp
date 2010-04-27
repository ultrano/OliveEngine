#include "OvProperty.h"

void*			OvProperty::Access(OvObject* pObj)
{
	if (pObj)
	{
		return (void*)(((char*)pObj) + GetOffset());
	}
	return (void*)0;
}
unsigned int	OvProperty::GetOffset()
{
	return m_uiOffset;
}
void			OvProperty::SetOffset(unsigned int uiOffset)
{
	m_uiOffset = uiOffset;
}

std::string&			OvProperty::GetPropertyName()
{
	return m_strPropertyName;
}
void			OvProperty::SetPropertyName(const std::string& strPropName)
{
	m_strPropertyName = strPropName;
}