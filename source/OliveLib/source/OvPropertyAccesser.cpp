#include "OvPropertyAccesser.h"
OvRTTI_IMPL_ROOT(OvPropertyAccesser);

OvPropertyAccesser::OvPropertyAccesser()
{
};

OvPropertyAccesser::~OvPropertyAccesser()
{
	m_strPropertyName.clear();
};

void*			OvPropertyAccesser::Access(OvObject* pObj)
{
	if (pObj)
	{
		return (void*)(((char*)pObj) + GetOffset());
	}
	return (void*)0;
}
unsigned int	OvPropertyAccesser::GetOffset()
{
	return m_uiOffset;
}
void			OvPropertyAccesser::SetOffset(unsigned int uiOffset)
{
	m_uiOffset = uiOffset;
}

std::string&			OvPropertyAccesser::GetPropertyName()
{
	return m_strPropertyName;
}
void			OvPropertyAccesser::SetPropertyName(const std::string& strPropName)
{
	m_strPropertyName = strPropName;
}