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
		bool	IsSame( Type_1 typePointer0, Type_1 typePointer1 );

		template<typename Type_0, typename Type_1>
		Type_0*	IsTypeOf(const Type_1 typePointer);

		template<typename Type_0, typename Type_1>
		Type_0*	IsKindOf( Type_1 typePointer );

		#include "OvUtility_RTTI_Impl.h"

	}
};

namespace OvRTTI_Util = OvUtility::RTTI ;