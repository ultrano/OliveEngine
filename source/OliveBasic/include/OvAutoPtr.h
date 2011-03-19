#pragma once
#include "OvTypeDef.h"
/*
//
//	[OvAutoPtr]�� OvMemObject�� ��ӹ��� ��ü���� ��Ȯ�� �޸𸮰����� �޽��ϴ�.
//	OvMemObject�� ��ӹ��� ������, ���� ������ü�� ���ؼ��� [OvAutoPtr]��ü�� ���� ��Ȯ�� ������ �����մϴ�.
//	OvMemObject�� ��ӹ��� ��ü�� ���ؼ�, new�� ����� ���ϰ�ü,�迭��ü�� �������
//	[OvAutoPtr]�� �ı�� �Բ� �ϰ� ���� �˴ϴ�.
//
*/
template<typename Type_0>
template_class	OvAutoPtr
{
public:
	OvAutoPtr();
	OvAutoPtr(const OvAutoPtr& _sp);
	OvAutoPtr(Type_0* _pt);
	~OvAutoPtr();
	// �Ϲ� �����ͷ��� ���Կ����� ������ �����ϸ�, �������� �������� ���Ѵ�.
	// ������ ĳ���� ���۷��̴� �����ε�������, ������ �������� Ȱ������� ���� ������� �����Կ� �±��.

	//! check, is it valid
	operator			OvBool()const;

	//! access to rear pointer address
	Type_0*				GetRear()const;

	//! release holding ( use carefully )
	Type_0*				Release();

	Type_0&				operator *();
	Type_0*				operator ->();
	OvAutoPtr&			operator = (const OvAutoPtr& _copy);
	OvAutoPtr&			operator = ( Type_0* _pt);

	template<typename Tyep_Count>
	Type_0&				operator [](Tyep_Count _ArrayCount);

private:
	Type_0*	m_pReferenceTarget;
};
#include "OvAutoPtr.inl"

/*
//
//	[OvArrayAutoPtr]�� ���� �迭��ü�� ���� �ϱ� ���� ���۵Ǿ�����,
//	[OvArrayAutoPtr]�� OvMemObject�� ��ӹ��� ����(������ ���۵�)
//	�迭��ü(������ü����)�� �����ϱ� ���� ����� �����ϴ�. 
//
*/
template<typename Type_0>
template_class	OvArrayAutoPtr 
{
public:
	OvArrayAutoPtr();
	OvArrayAutoPtr(OvArrayAutoPtr& _sp);
	OvArrayAutoPtr(Type_0* _pt);
	~OvArrayAutoPtr();

	//! check, is it valid
	operator			OvBool()const;

	//! access to rear pointer address
	Type_0*				GetRear()const;

	Type_0&					operator *();
	Type_0*					operator ->();
	OvArrayAutoPtr&			operator = (const OvArrayAutoPtr& _copy);
	OvArrayAutoPtr&			operator = ( Type_0* _pt);

	template<typename Tyep_Count>
	Type_0&				operator [](Tyep_Count _ArrayCount);

private:
	Type_0*	m_pReferenceTarget;
};
#include "OvArrayAutoPtr.inl"