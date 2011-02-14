#pragma once

#include <windows.h>
#include <assert.h>
#include <math.h>
#include <stdlib.h>

#include "OvGlobalFunc.h"
#include "OvConvert.h"
#include "OvUtility_RTTI.h"
#include "OvMacro.h"
#include "OvThreadSync.h"

//////////////////////////////////////////////////////////////////////////
#include <algorithm>
namespace OU
{
	namespace container
	{
		template<typename C, typename V>
		bool remove( C& c, const V& v )
		{
			return (c.end() != std::remove( c.begin(), c.end(), v ) );
		}

		template<typename C, typename V>
		typename C::iterator find( C& c, const V& v )
		{
			return std::find( c.begin(), c.end(), v );
		}

	}
}
//////////////////////////////////////////////////////////////////////////