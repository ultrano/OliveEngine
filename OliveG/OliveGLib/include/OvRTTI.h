#pragma once
#include <string>

using namespace std;

class OvPropertyBag;
class	OvRTTI{

public:

	enum
	{
		OvRTTI_MAX_PARENT_COUNT = 2
	};

	OvRTTI(const string & classname)
		:m_strClassName(classname)
		,m_pPropertyBag(NULL)
	{
		m_pBaseClassRTTI[0] = NULL;
		m_pBaseClassRTTI[1] = NULL;
	};
	OvRTTI(const string & classname, const OvRTTI& baseclass)
		:m_strClassName(classname)
		,m_pPropertyBag(NULL)
	{
		m_pBaseClassRTTI[0] = &baseclass;
		m_pBaseClassRTTI[1] = NULL;
	};

	void					SetPropertyBag(OvPropertyBag* propBag){m_pPropertyBag = propBag;};
	inline OvPropertyBag*	PropertyBag(){return m_pPropertyBag;};
	inline const char*	TypeName(){return m_strClassName.data();};
	const OvRTTI*		GetBaseRTTI(unsigned int uiIndex = 0){return m_pBaseClassRTTI[uiIndex];};

private:

	const string					m_strClassName;

	const OvRTTI*					m_pBaseClassRTTI[OvRTTI_MAX_PARENT_COUNT];

	OvPropertyBag*					m_pPropertyBag;

};
