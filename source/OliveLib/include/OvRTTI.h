#pragma once

using namespace std;

class OvPropertyBag;
class	OvRTTI{

public:

	enum
	{
		// ����Ŭ������ �ִ� 2�������� ������ �ϵ��� �������.
		// �⺻���� ���� Ŭ���� �Ѱ����� �������̽� Ŭ���� �ϳ���
		// RTTI�� �����Ѵ�.
		// �� �̻��� ���߻���� �������� ������ ���� ��Ű��
		// ǥ�ؿ����� ����� ���� �߼��̴�.
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
