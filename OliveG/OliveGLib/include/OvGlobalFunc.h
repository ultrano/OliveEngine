#pragma once
#include <Windows.h>
#include <string>

void	OvGetLastError();

void	OvMessageBox(const char* _msg,const char* _caption);

void	OvErrorMgrBox(const char* _file,const char* _block,const char* _msg = NULL);

bool	OvStringAllocator(LPTSTR* _lpp_dest,LPCTSTR lp_src);

std::string	OvGetDirectoryInFullFilePath(const std::string& strFileFullPath);
std::string	OvGetFileNameInFullFilePath(const std::string& strFileFullPath);
std::string	OvGetExtentionInFullFilePath(const std::string& strFileFullPath);
