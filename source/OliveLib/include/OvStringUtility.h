#pragma once
#include "OvMemObject.h"
#include "OvAutoPtr.h"

class OvFormatString : public OvMemObject
{
public:
	OvFormatString();
	OvFormatString(const OvChar* _pFormat,...);
	OvChar* operator()(const OvChar* _pFormat,...);
	operator OvChar*();
protected:
private:
	OvArrayAutoPtr<OvChar>	m_pBuffer;
};


/*
class	OvLexical 
{
public:
	enum{LEXICAL_BUFLEN=64};
	OvLexical(){};
	virtual ~OvLexical(){};
public:
	OvChar* operator()(DWORD _UnsignedLong)
	{
		sprintf(m_CovertedString,"%d",_UnsignedLong);
		return (OvChar*)m_CovertedString;
	};
	OvChar* operator()(OvFloat _UnsignedLong)
	{
		sprintf(m_CovertedString,"%f",_UnsignedLong);
		return (OvChar*)m_CovertedString;
	};

private:

	OvChar	m_CovertedString[LEXICAL_BUFLEN];

};
*/