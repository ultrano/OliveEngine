#pragma once

#include "OvRTTI.h"

namespace OvUtility
{
	namespace RTTI
	{
		#define	OvRTTI_DECL_ROOT( classname )
		#define	OvRTTI_DECL( classname )
		#define	OvRTTI_IMPL_ROOT( classname )
		#define	OvRTTI_IMPL( classname )

		template<typename Type_0>
		const OvString&	TypeName( Type_0 typePointer );

		template<typename Type_0, typename Type_1>
		OvBool	IsSame( Type_1 typePointer0, Type_1 typePointer1 );

		template<typename Type_0, typename Type_1>
		Type_0*	IsTypeOf(const Type_1 typePointer);

		template<typename Type_0, typename Type_1>
		Type_0*	IsKindOf( Type_1 typePointer );

		#include "OvUtility_RTTI_Impl.h"

	}
};

template<typename Type_0>
const OvString&	OvTypeName( Type_0 typePointer )
{
	return OvRTTI_Util::TypeName<Type_0>( typePointer );
}

template<typename Type_0, typename Type_1>
OvBool	OvIsSame( Type_1 typePointer0, Type_1 typePointer1 )
{
	return OvRTTI_Util::IsSame( typePointer0, typePointer1 );
}

template<typename Type_0, typename Type_1>
Type_0*	OvIsTypeOf(const Type_1 typePointer)
{
	return OvRTTI_Util::IsTypeOf<Type_0>( typePointer );
}

template<typename Type_0, typename Type_1>
Type_0*	OvIsKindOf( Type_1 typePointer )
{
	return OvRTTI_Util::IsKindOf<Type_0>( typePointer );
}

template<typename Type_0, typename Type_1>
Type_0*	OvCastTo( Type_1 typePointer )
{
	//!< 내부적 동작이 케스팅과 같으므로 IsKindOf를 사용.
	return OvRTTI_Util::IsKindOf<Type_0>( typePointer );
}

namespace OvRTTI_Util = OvUtility::RTTI ;