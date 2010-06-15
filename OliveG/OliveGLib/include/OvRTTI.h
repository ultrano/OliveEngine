#pragma once
#include <string>

using namespace std;

class OvPropertyBag;
class	OvRTTI{

public:

	enum
	{
		// 슈퍼클레스는 최대 2개까지만 지원을 하도록 만들었다.
		// 기본적인 구현 클레스 한가지와 인터페이스 클레스 하나만
		// RTTI가 지원한다.
		// 그 이상의 다중상속은 가독성과 성능을 저하 시키며
		// 표준에서도 사라져 가는 추세이다.
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
