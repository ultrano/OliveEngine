#define	EXPORTDLL
#include "IniFile.h"

bool CIniFile::Open(const char *_FileName){

	if( ! _FileName){
		return false;
	}

	m_FineName = _FileName;

	return true;

};


void CIniFile::Close(){

	m_FineName.clear();

};


const char*		CIniFile::GetString(char *_Section,const char *_ValueName){

	if(!_Section || !_ValueName){
		return false;
	}

	char kpBuffer[1024] = {0,};

	GetPrivateProfileString(_Section,_ValueName,"",reinterpret_cast<LPSTR>(kpBuffer),1024,m_FineName.data());

	m_strString = kpBuffer;

	return m_strString.data();

};