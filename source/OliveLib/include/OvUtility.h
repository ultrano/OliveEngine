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
		void remove( C& c, const V& v )
		{
			c.erase( std::remove( c.begin(), c.end(), v ), c.end());
		}

		template<typename C, typename V>
		typename C::iterator find( C& c, const V& v )
		{
			return std::find( c.begin(), c.end(), v );
		}

		template<typename Ret, typename C>
		typename Ret convert( C& c )
		{
			Ret ret;
			for each( const C::value_type& val in c )
			{
				ret.push_back( val );
			}
			return ret;
		}

	}
}
//////////////////////////////////////////////////////////////////////////