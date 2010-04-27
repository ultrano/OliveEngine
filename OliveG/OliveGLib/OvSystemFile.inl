
#include "IniFile.h"

template<typename T>
bool	CIniFile::SetValue(char *_Section,const char *_ValueName,T _Value){

	if(!_Section || !_ValueName){
		return false;
	}

	return WritePrivateProfileString(_Section,_ValueName,lexical_cast<string>(_Value).data(),m_FineName.data());

};

template<typename T>
T		CIniFile::GetValue(char *_Section,const char *_ValueName){

	if(!_Section || !_ValueName){
		return false;
	}

	char kpBuffer[1024] = {0,};

	GetPrivateProfileString(_Section,_ValueName,"",reinterpret_cast<LPSTR>(kpBuffer),1024,m_FineName.data());

	m_strValue = kpBuffer;

	return lexical_cast<T>(m_strValue.data());

};

