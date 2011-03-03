#pragma once
#pragma warning( disable : 4521 )
#pragma warning( disable : 4522 )
#pragma warning( disable : 4311 )

#include "OvRefBase.h"

template<typename T>
template_class OvSmartPointer;

template<typename Type_0>
template_class	OvWeakPointer : public OvMemObject
{
public:
	OvWeakPointer();
	OvWeakPointer( OvWeakPointer& _pointer);
	OvWeakPointer(const OvWeakPointer& _pointer);
	template<typename Type_1>
	OvWeakPointer(const OvWeakPointer<Type_1>& _pointer);


	OvWeakPointer( OvSmartPointer<Type_0>& _pointer);
	OvWeakPointer(const OvSmartPointer<Type_0>& _pointer);
	template<typename Type_1>
	OvWeakPointer(const OvSmartPointer<Type_1>& _pointer);


	OvWeakPointer(Type_0* _pt);
	~OvWeakPointer();

	//! access to rear pointer address
	Type_0*				GetRear()const;

	//! query is it expired
	OvBool				Expired();

	//! check, is it valid
	operator			OvInt()const;

	Type_0&				operator [](OvInt _ArrayCount);
	Type_0*				operator ->()const;
	OvWeakPointer&		operator = ( Type_0* _pt);

	OvWeakPointer&		operator = ( OvWeakPointer& _copy);
	OvWeakPointer&		operator = (const OvWeakPointer& _copy);

	template<typename Type_1>
	OvWeakPointer&		operator = (const OvWeakPointer<Type_1>& _copy);


	OvWeakPointer&		operator = ( OvSmartPointer<Type_0>& _copy);
	OvWeakPointer&		operator = (const OvSmartPointer<Type_0>& _copy);

	template<typename Type_1>
	OvWeakPointer&		operator = (const OvSmartPointer<Type_1>& _copy);

private:
	Type_0*	m_ref_target;
};
#include "OvWeakPointer.inl"
