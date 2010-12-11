#pragma once
#include "OvTypeDef.h"
/*
//
//	[OvAutoPtr]은 OvMemObject를 상속받은 객체여야 정확한 메모리관리를 받습니다.
//	OvMemObject를 상속받지 않으면, 단일 동적객체에 한해서만 [OvAutoPtr]객체에 의해 정확한 삭제가 가능합니다.
//	OvMemObject를 상속받은 객체에 한해서, new를 사용한 단일객체,배열객체에 관계없이
//	[OvAutoPtr]의 파기와 함께 일괄 삭제 됩니다.
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
	// 일반 포인터로의 대입연산은 굉장히 위험하며, 안전성을 보장하지 못한다.
	// 위험한 캐스팅 오퍼래이더 오버로드이지만, 사용상의 유연성과 활용범위를 위해 사용자의 현명함에 맞긴다.

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
//	[OvArrayAutoPtr]은 동적 배열객체를 관리 하기 위해 제작되었으며,
//	[OvArrayAutoPtr]은 OvMemObject를 상속받지 못한(기존에 제작된)
//	배열객체(동적객체집단)를 관리하기 위해 만들어 졌습니다. 
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