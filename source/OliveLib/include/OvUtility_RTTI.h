#pragma once

#include "OvRTTI.h"
#pragma once
/*
#define	OvRTTI_DECL_ROOT( classname )
#define	OvRTTI_DECL( classname )
#define	OvRTTI_DECL_EX(classname,baseclass1,baseclass2)
#define	OvRTTI_IMPL_ROOT( classname )
#define	OvRTTI_IMPL( classname )
#define	OvRTTI_IMPL_EX(classname)

template<typename Type_0>
const OvString&	OvTypeName( Type_0 typePointer );

template<typename Type_0, typename Type_1>
OvBool	OvIsSame( Type_1 typePointer0, Type_1 typePointer1 );

template<typename Type_0, typename Type_1>
Type_0*	OvIsTypeOf(const Type_1 typePointer);

template<typename Type_0, typename Type_1>
Type_0*	OvIsKindOf( Type_1 typePointer );

template<typename Type_0, typename Type_1>
Type_0*	OvCastTo( Type_1 typePointer );
*/

//////////////////////////////////////////////////////////////////////////

#ifdef OvRTTI_DECL_ROOT
#undef OvRTTI_DECL_ROOT
#endif


#define	OvRTTI_DECL_ROOT(classname) \
private:\
	static const OvRTTI msh_OvRTTI;\
public:\
	static const OvRTTI*	GetRTTI(){return &classname::msh_OvRTTI;};\
	virtual const OvRTTI* QueryRTTI()const{return &msh_OvRTTI;};\
	classname*				_this_pointer(){ return this; };\
	typedef classname __this_class;

//////////////////////////////////////////////////////////////////////////

//////////////////////////////////////////////////////////////////////////

#ifdef OvRTTI_DECL
#undef OvRTTI_DECL
#endif


#define	OvRTTI_DECL(classname) \
private:\
	static const OvRTTI msh_OvRTTI;\
public:\
	static const OvRTTI*	GetRTTI(){return &classname::msh_OvRTTI;};\
	static const OvRTTI*	GetBaseRTTI(){return __super::GetRTTI();};\
	virtual const OvRTTI*	QueryRTTI()const{return &classname::msh_OvRTTI;};\
	classname*				_this_pointer(){ return this; };\
	typedef classname __this_class;

//////////////////////////////////////////////////////////////////////////

#ifdef OvRTTI_DECL_EX
#undef OvRTTI_DECL_EX
#endif

#define	OvRTTI_DECL_EX(classname,baseclass1,baseclass2) \
private:\
	static const OvRTTI msh_OvRTTI;\
public:\
	static const OvRTTI*	GetRTTI(){return &classname::msh_OvRTTI;};\
	static const OvRTTI*	GetBaseRTTI1(){return baseclass1::GetRTTI();};\
	static const OvRTTI*	GetBaseRTTI2(){return baseclass2::GetRTTI();};\
	virtual const OvRTTI*	QueryRTTI()const{return &classname::msh_OvRTTI;};\
	classname*				_this_pointer(){ return this; };\
	typedef classname __this_class;

//////////////////////////////////////////////////////////////////////////

//////////////////////////////////////////////////////////////////////////
//////////////////////////////////////////////////////////////////////////

#ifdef OvRTTI_IMPL_ROOT
#undef OvRTTI_IMPL_ROOT
#endif


#define	OvRTTI_IMPL_ROOT(classname) const OvRTTI classname::msh_OvRTTI(#classname);

//////////////////////////////////////////////////////////////////////////

//////////////////////////////////////////////////////////////////////////

#ifdef OvRTTI_IMPL
#undef OvRTTI_IMPL
#endif


#define	OvRTTI_IMPL(classname) const OvRTTI classname::msh_OvRTTI(#classname,*(classname::GetBaseRTTI()));

//////////////////////////////////////////////////////////////////////////

//////////////////////////////////////////////////////////////////////////

#ifdef OvRTTI_IMPL_EX
#undef OvRTTI_IMPL_EX
#endif


#define	OvRTTI_IMPL_EX(classname) const OvRTTI classname::msh_OvRTTI(#classname,*(classname::GetBaseRTTI1()),*(classname::GetBaseRTTI2()));

//////////////////////////////////////////////////////////////////////////

template<typename Type_0>
Type_0*	_TraverseTypeTree(const OvRTTI* typeInfo)
{
	if ( NULL == typeInfo )
	{
		return (Type_0*)false;
	}
	if ( Type_0::GetRTTI() == typeInfo )
	{
		return (Type_0*)true;
	}

	for ( unsigned i = 0 ; i < OvRTTI::OvRTTI_MAX_PARENT_COUNT ; ++i )
	{
		if ( _TraverseTypeTree< Type_0 >( const_cast<OvRTTI*>(typeInfo)->GetBaseRTTI( i ) ) )
		{
			return (Type_0*)true;
		}
	}

	return (Type_0*)false;

}

//////////////////////////////////////////////////////////////////////////
namespace OU
{
	namespace rtti
	{
		template<typename Type_0>
		const OvString&	OvTypeName( Type_0 typePointer )
		{
			if (typePointer)
			{
				return (const_cast<OvRTTI*>(typePointer->QueryRTTI()))->TypeName();
			}
			static OvString emptyName = "";
			return emptyName;
		}

		//////////////////////////////////////////////////////////////////////////

		//////////////////////////////////////////////////////////////////////////

		template<typename Type_0, typename Type_1>
		OvBool	OvIsSame( Type_1 typePointer0, Type_1 typePointer1 )
		{
			if ( typePointer0 && typePointer1 )
			{
				return typePointer0->QueryRTTI() == typePointer1->QueryRTTI();
			}
			return false;
		}

		//////////////////////////////////////////////////////////////////////////
		template<typename Type_0, typename Type_1>
		Type_0*	OvIsTypeOf(const Type_1 typePointer)
		{
			if ( NULL != typePointer->_this_pointer() && Type_0::GetRTTI() == typePointer->QueryRTTI() )
			{
				return static_cast<Type_0*>( typePointer->_this_pointer() );
			}
			return NULL;
		}
		//////////////////////////////////////////////////////////////////////////


		template<typename Type_0, typename Type_1>
		Type_0*	OvIsKindOf( Type_1 typePointer )
		{
			if( NULL == typePointer->_this_pointer() )
				return NULL;

			const OvRTTI* kpRTTI = typePointer->QueryRTTI();

			return _TraverseTypeTree<Type_0>(kpRTTI);

		}
		//////////////////////////////////////////////////////////////////////////

		template<typename Type_0, typename Type_1>
		Type_0*	OvCastTo( Type_1 typePointer )
		{
			if( NULL == typePointer->_this_pointer() )
				return NULL;

			const OvRTTI* kpRTTI = typePointer->QueryRTTI();

			return ( _TraverseTypeTree<Type_0>(kpRTTI) )? (Type_0*)typePointer->_this_pointer():NULL;
		}
	}
}

//! 자주 사용하므로 기본 네임스페이스로 지정해놓자.
using namespace OU::rtti;