#pragma once

using namespace std;

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
	{
		m_pBaseClassRTTI[0] = NULL;
		m_pBaseClassRTTI[1] = NULL;
	};
	OvRTTI(const OvString & classname, const OvRTTI& baseclass)
		:m_strClassName(classname)
	{
		m_pBaseClassRTTI[0] = &baseclass;
		m_pBaseClassRTTI[1] = NULL;
	};
	OvRTTI(const OvString & classname, const OvRTTI& baseclass1, const OvRTTI& baseclass2)
		:m_strClassName(classname)
	{
		m_pBaseClassRTTI[0] = &baseclass1;
		m_pBaseClassRTTI[1] = &baseclass2;
	};

	inline const OvString&	TypeName() const {return m_strClassName;};
	const OvRTTI*		GetBaseRTTI(OvUInt uiIndex = 0){return m_pBaseClassRTTI[uiIndex];};

private:

	const OvString					m_strClassName;

	const OvRTTI*					m_pBaseClassRTTI[OvRTTI_MAX_PARENT_COUNT];

};
