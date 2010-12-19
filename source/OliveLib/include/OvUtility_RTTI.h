#pragma once

#include "OvRTTI.h"

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

#include "OvUtility_RTTI_Impl.h"