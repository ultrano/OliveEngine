#pragma once
#include "OvTypeDef.h"

namespace OU
{
	namespace path
	{
		OvString GetBasePath( const OvString& path );
		OvString GetExtention( const OvString& path );
		OvString GetFileName( const OvString& path );
		OvString GetFileSpec( const OvString& path );
	}
}