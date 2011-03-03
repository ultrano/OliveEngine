#pragma once
#pragma warning( disable : 4521 )
#pragma warning( disable : 4522 )
#pragma warning( disable : 4311 )

#include "OvRefBase.h"

template<typename T>
template_class OvWeakPointer;

template<typename Type_0>
template_class	OvSmartPointer : public OvMemObject
{
public:
	OvSmartPointer();
	OvSmartPointer( OvSmartPointer& _pointer);
	OvSmartPointer(const OvSmartPointer& _pointer);
	template<typename Type_1>
	OvSmartPointer(const OvSmartPointer<Type_1>& _pointer);


	OvSmartPointer( OvWeakPointer<Type_0>& _pointer);
	OvSmartPointer(const OvWeakPointer<Type_0>& _pointer);
	template<typename Type_1>
	OvSmartPointer(const OvWeakPointer<Type_1>& _pointer);

	OvSmartPointer(Type_0* _pt);
	~OvSmartPointer();

	//! access to rear pointer address
	Type_0*				GetRear()const;

	//! check, is it valid
	operator			OvInt()const;

	Type_0*				operator ->()const;
	OvSmartPointer&		operator = ( Type_0* _pt);
	OvSmartPointer&		operator = ( OvSmartPointer& _copy);
	OvSmartPointer&		operator = (const OvSmartPointer& _copy);
	OvSmartPointer&		operator = ( OvWeakPointer<Type_0>& _copy);
	OvSmartPointer&		operator = (const OvWeakPointer<Type_0>& _copy);
	Type_0&				operator [](OvInt _ArrayCount);

	template<typename Type_1>
	OvSmartPointer&		operator = (const OvSmartPointer<Type_1>& _copy);
	template<typename Type_1>
	OvSmartPointer&		operator = (const OvWeakPointer<Type_1>& _copy);

private:
	Type_0*	m_ref_target;
};
#include "OvSmartPointer.inl"
