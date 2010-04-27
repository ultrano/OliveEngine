#pragma once
#include "OvMemObject.h"
#include "OvAutoPtr.h"

class OvFormatString : public OvMemObject
{
public:
	OvFormatString();
	OvFormatString(const char* _pFormat,...);
	char* operator()(const char* _pFormat,...);
	operator char*();
protected:
private:
	OvAutoArrayPtr<char>	m_pBuffer;
};



class	OvLexical 
{
public:
	enum{LEXICAL_BUFLEN=64};
	OvLexical(){};
	virtual ~OvLexical(){};
public:
	char* operator()(DWORD _UnsignedLong)
	{
		sprintf(m_CovertedString,"%d",_UnsignedLong);
		return (char*)m_CovertedString;
	};
	char* operator()(float _UnsignedLong)
	{
		sprintf(m_CovertedString,"%f",_UnsignedLong);
		return (char*)m_CovertedString;
	};

private:

	char	m_CovertedString[LEXICAL_BUFLEN];

};
