#pragma once


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

template<typename Type_0>
const string&	TypeName( Type_0 typePointer )
{
	if (typePointer)
	{
		return (const_cast<OvRTTI*>(typePointer->QueryRTTI()))->TypeName();
	}
	static string emptyName = "";
	return emptyName;
}

//////////////////////////////////////////////////////////////////////////

//////////////////////////////////////////////////////////////////////////

template<typename Type_0, typename Type_1>
bool	IsSame( Type_1 typePointer0, Type_1 typePointer1 )
{
	if ( typePointer0 && typePointer1 )
	{
		return typePointer0->QueryRTTI() == typePointer1->QueryRTTI();
	}
	return false;
}

//////////////////////////////////////////////////////////////////////////
template<typename Type_0, typename Type_1>
Type_0*	IsTypeOf(const Type_1 typePointer)
{
	if ( NULL != typePointer->_this_pointer() && Type_0::GetRTTI() == typePointer->QueryRTTI() )
	{
		return static_cast<Type_0*>( typePointer->_this_pointer() );
	}
	return NULL;
}
//////////////////////////////////////////////////////////////////////////


template<typename Type_0, typename Type_1>
Type_0*	IsKindOf(Type_1 typePointer)
{
	if( NULL == typePointer->_this_pointer() )
		return NULL;

	const OvRTTI* kpRTTI = typePointer->QueryRTTI();

	return _TraverseTypeTree<Type_0>(kpRTTI);

}

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