#pragma once

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

	OvRTTI(const OvString & classname)
		:m_strClassName(classname)
		,m_pPropertyBag(NULL)
	{
		m_pBaseClassRTTI[0] = NULL;
		m_pBaseClassRTTI[1] = NULL;
		_inherit_count() = 0;
	};
	OvRTTI(const OvString & classname, const OvRTTI& baseclass)
		:m_strClassName(classname)
		,m_pPropertyBag(NULL)
	{
		m_pBaseClassRTTI[0] = &baseclass;
		m_pBaseClassRTTI[1] = NULL;
		_inherit_count() = baseclass._inherit_count() + 1;
	};
	OvRTTI(const OvString & classname, const OvRTTI& baseclass1, const OvRTTI& baseclass2)
		:m_strClassName(classname)
		,m_pPropertyBag(NULL)
	{
		m_pBaseClassRTTI[0] = &baseclass1;
		m_pBaseClassRTTI[1] = &baseclass2;
		_inherit_count() = min( baseclass1._inherit_count(), baseclass1._inherit_count() ) + 1;
	};

	void					SetPropertyBag(OvPropertyBag* propBag){m_pPropertyBag = propBag;};
	inline OvPropertyBag*	PropertyBag(){return m_pPropertyBag;};
	inline const OvString&	TypeName() const {return m_strClassName;};
	const OvRTTI*			GetBaseRTTI(OvUInt uiIndex = 0){return m_pBaseClassRTTI[uiIndex];};
public:
	OvUInt&			_inherit_count() const { static OvUInt inherit_count; return inherit_count; };
private:

	const OvString	m_strClassName;

	const OvRTTI*	m_pBaseClassRTTI[OvRTTI_MAX_PARENT_COUNT];

	OvPropertyBag*	m_pPropertyBag;


};
