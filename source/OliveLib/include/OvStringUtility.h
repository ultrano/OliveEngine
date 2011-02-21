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
namespace OU
{
	namespace string
	{
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

		inline OvString split (	OvString & s, 
								const OvString delim = " ",
								const bool trim_spaces = true)
		{

			// find delimiter  
			OvString::size_type i (s.find (delim));

			// split into before and after delimiter
			OvString w (s.substr (0, i));

			// if no delimiter, remainder is empty
			if (i == OvString::npos)
				s.erase ();
			else
				// erase up to the delimiter
				s.erase (0, i + delim.size ());

			// trim spaces if required
			if (trim_spaces)
			{
				w = trim (w);
				s = trim (s);
			}

			// return first word in line
			return w;

		}
	}
}