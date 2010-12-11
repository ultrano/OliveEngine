#pragma once
#pragma warning( disable : 4521 )
#pragma warning( disable : 4522 )
#include "OvRefBase.h"
#define OvREF_POINTER(__class_name)	class __class_name;\
	typedef OvSmartPointer<__class_name>	__class_name##SPtr;

template<typename Type_0>
template_class	OvSmartPointer : public OvMemObject
{
public:
	OvSmartPointer();
	OvSmartPointer( OvSmartPointer& _pointer);
	OvSmartPointer(const OvSmartPointer& _pointer);
	template<typename Type_1>
	OvSmartPointer(const OvSmartPointer<Type_1>& _pointer);
	OvSmartPointer(Type_0* _pt);
	~OvSmartPointer();

	//! access to rear pointer address
	Type_0*				GetRear()const;

	//! check, is it valid
	operator			OvBool()const;

	Type_0*				operator ->()const;
	OvSmartPointer&		operator = ( Type_0* _pt);
	OvSmartPointer&		operator = ( OvSmartPointer& _copy);
	OvSmartPointer&		operator = (const OvSmartPointer& _copy);
	Type_0&				operator [](OvInt _ArrayCount);

	template<typename Type_1>
	OvSmartPointer&		operator = (const OvSmartPointer<Type_1>& _copy);

private:
	Type_0*	m_pReferenceTarget;
};
#include "OvSmartPointer.inl"
