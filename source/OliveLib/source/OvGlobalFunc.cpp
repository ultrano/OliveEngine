#include "OvGlobalFunc.h"
using namespace std;

void	OvGetLastError()
{
	LPVOID lpMsgBuf;

	FormatMessage( 
		FORMAT_MESSAGE_ALLOCATE_BUFFER | 
		FORMAT_MESSAGE_FROM_SYSTEM | 
		FORMAT_MESSAGE_IGNORE_INSERTS,
		NULL,
		GetLastError(),
		MAKELANGID(LANG_NEUTRAL, SUBLANG_DEFAULT), // Default language
		(LPTSTR) &lpMsgBuf,
		0,
		NULL 
		);
	MessageBox( NULL, (LPCTSTR)lpMsgBuf, "Error", MB_OK | MB_ICONINFORMATION );

	LocalFree( lpMsgBuf );
};

void	OvMessageBox(const char* _msg,const char* _caption)
{
	MessageBox(NULL,_msg,_caption,MB_OK);
}

void	OvErrorMgrBox(const char* _file,const char* _block,const char* _msg )
{
	char k_code_location[1024] = {0,};

	strcat(k_code_location,"File : ");
	strcat(k_code_location,_file);

	strcat(k_code_location,"\nBlock : ");
	strcat(k_code_location,_block);

	strcat(k_code_location,"\nAdditionMsg : ");
	strcat(k_code_location,_msg);

	MessageBox(NULL, k_code_location ,"[Run time error]",MB_OK);

}

bool		OvStringAllocator(LPTSTR* _lpp_dest,LPCTSTR lp_src)
{
	if (!lp_src)
	{
		return false;
	}
	size_t	k_len = strlen(lp_src) + 1;
	*_lpp_dest = new CHAR[k_len];
	memset((void*)(*_lpp_dest),0,k_len*sizeof(CHAR));
	if (!(*_lpp_dest))
	{
		return false;
	}
	memcpy((void*)(*_lpp_dest),(void*)lp_src,k_len*sizeof(CHAR));
	return true;
};
string	OvGetDirectoryInFullFilePath(const string& strFileFullPath)
{
	string kReturnString= "";
	size_t stTok = strFileFullPath.rfind('/');
	if (stTok != string::npos)
	{
		kReturnString = strFileFullPath;
		kReturnString.resize(stTok+1);
	}
	return kReturnString;
}
std::string	OvGetFileNameInFullFilePath(const std::string& strFileFullPath)
{
	string kReturnString= "";
	size_t stTok = strFileFullPath.rfind('/');
	if (stTok != string::npos)
	{
		kReturnString = &strFileFullPath[stTok+1];
		stTok = kReturnString.rfind('.');
		kReturnString.resize(stTok);
	}
	return kReturnString;
}
std::string	OvGetExtentionInFullFilePath(const std::string& strFileFullPath)
{
	string kReturnString= "";
	size_t stTok = strFileFullPath.rfind('.');
	if (stTok != string::npos)
	{
		kReturnString = &strFileFullPath[stTok];
	}
	return kReturnString;
}
/*inline bool		OvStringAllocator(const char** _lpp_dest,const char* lp_src)
{
if (!lp_src)
{
return false;
}
std::string	k_src(lp_src);
*_lpp_dest = new char[k_src.length()];
memset((void*)(*_lpp_dest),0,k_src.length()*sizeof(char));
if (!(*_lpp_dest))
{
return false;
}
memcpy((void*)(*_lpp_dest),(void*)k_src.data(),k_src.length()*sizeof(char));
return true;
};*/
