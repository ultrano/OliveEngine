#pragma once
#include "OvTypeDef.h"
#include <Windows.h>

void	OvGetLastError();

void	OvMessageBox(const char* _msg,const char* _caption);

void	OvErrorMsgBox(const char* _file,const char* _block,const char* _msg = NULL);

bool	OvStringAllocator(LPTSTR* _lpp_dest,LPCTSTR lp_src);

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

	unsigned int Factorial( unsigned int total);
	unsigned int Factorial( unsigned int total, unsigned int select );
	unsigned int Combination( unsigned int total, unsigned int select );
	unsigned int Sigma( unsigned int total);
}