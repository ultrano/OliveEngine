#pragma once
#ifdef	EXPORTDLL
#define	CLASSDLLTYPE __declspec(dllexport)
#else
#define	CLASSDLLTYPE __declspec(dllimport)
#endif

#include <windows.h>
#include<boost/lexical_cast.hpp>
#include <string>
using namespace boost;
using namespace std;

class CLASSDLLTYPE CIniFile{

public:

	bool	Open(const char *_FileName);

	void	Close();

	template<typename T>
	bool	SetValue(char *_Section,const char *_ValueName,T _Value);
	template<typename T>
	T		GetValue(char *_Section,const char *_ValueName);

	const char*		GetString(char *_Section,const char *_ValueName);

private:

	string		m_FineName;

	std::string	m_strValue;

	std::string	m_strString;


};

#include "IniFile.inl"


