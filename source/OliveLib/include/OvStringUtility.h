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

// 출처 : http://www.gammon.com.au/forum/bbshowpost.php?bbsubject_id=2896
// ㅜ_ㅜ 좋당.
#define SPACES " \t\r\n"

inline OvString trim_right (const OvString & s, const OvString & t = SPACES)
{ 
	OvString d (s); 
	OvString::size_type i (d.find_last_not_of (t));
	if (i == OvString::npos)
		return "";
	else
		return d.erase (d.find_last_not_of (t) + 1) ; 
}  // end of trim_right

inline OvString trim_left (const OvString & s, const OvString & t = SPACES) 
{ 
	OvString d (s); 
	return d.erase (0, s.find_first_not_of (t)) ; 
}  // end of trim_left

inline OvString trim (const OvString & s, const OvString & t = SPACES)
{ 
	OvString d (s); 
	return trim_left (trim_right (d, t), t) ; 
}  // end of trim


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