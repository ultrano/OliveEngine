#pragma once
#include "OvTypeDef.h"
#include <Windows.h>

void	OvGetLastError();

void	OvMessageBox(const OvChar* _msg,const OvChar* _caption);

void	OvErrorMsgBox(const OvChar* _file,const OvChar* _block, const OvUInt _line, const OvChar* _msg = NULL );

OvBool	OvStringAllocator(LPTSTR* _lpp_dest,LPCTSTR lp_src);

OvString	OvGetDirectoryInFullFilePath(const OvString& strFileFullPath);
OvString	OvGetFileNameInFullFilePath(const OvString& strFileFullPath);
OvString	OvGetExtentionInFullFilePath(const OvString& strFileFullPath);

namespace OvConvert
{

	template< typename T0, typename T1 >
	T0	xy( const T1& src )
	{
		T0 dest;
		dest.x = src.x;
		dest.y = src.y;
		return dest;
	};

	template< typename T0, typename T1 >
	T0	xyz( const T1& src )
	{
		T0 dest;
		dest.x = src.x;
		dest.y = src.y;
		dest.z = src.z;
		return dest;
	};

	template< typename T0, typename T1 >
	T0	xyzw( const T1& src )
	{
		T0 dest;
		dest.x = src.x;
		dest.y = src.y;
		dest.z = src.z;
		dest.w = src.w;
		return dest;
	};
};

namespace OvMath
{

	OvUInt Factorial( OvUInt total);
	OvUInt Factorial( OvUInt total, OvUInt select );
	OvUInt Combination( OvUInt total, OvUInt select );
	OvUInt Sigma( OvUInt total);
}