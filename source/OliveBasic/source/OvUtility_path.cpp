#include "OvUtility_path.h"
#include <atlpath.h>

OvString OU::path::GetBasePath( const OvString& path )
{
	OvString ret = path;
	ATL::ATLPath::RemoveFileSpec( &ret[0] );
	return ret;
}

OvString OU::path::GetExtention( const OvString& path )
{
	OvString ret;
	if ( OvChar* ext = ATL::ATLPath::FindExtension( &path[0] ) )
	{
		ret = ext;
	}
	return ret;
}

OvString OU::path::GetFileName( const OvString& path )
{
	OvString ret;
	if ( OvChar* file = ATL::ATLPath::FindFileName( &path[0] ) )
	{
		ret = file;
	}
	return ret;
}

OvString OU::path::GetFileSpec( const OvString& path )
{
	OvString ret;
	if ( OvChar* file = ATL::ATLPath::FindFileName( &path[0] ) )
	{
		ret = file;
		ATL::ATLPath::RemoveExtension( &ret[0] );
	}
	return ret;
}
