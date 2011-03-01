#include "OvUtility_string.h"
#include <stdarg.h>

namespace OU
{
	// √‚√≥ : http://www.gammon.com.au/forum/bbshowpost.php?bbsubject_id=2896

	namespace string
	{

		OvString trim_right (const OvString & s, const OvString & t )
		{ 
			OvString d (s); 
			OvString::size_type i (d.find_last_not_of (t));
			if (i == OvString::npos)
				return "";
			else
				return d.erase (d.find_last_not_of (t) + 1) ; 
		}  // end of trim_right
		OvString trim_left (const OvString & s, const OvString & t ) 
		{ 
			OvString d (s); 
			return d.erase (0, s.find_first_not_of (t)) ; 
		}  // end of trim_left
		OvString trim (const OvString & s, const OvString & t )
		{ 
			OvString d (s); 
			return trim_left (trim_right (d, t), t) ; 
		}  // end of trim
		OvString split (	OvString & s, 
			const OvString & delim,
			const bool trim_spaces )
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
		OvString format( const OvChar* form, ...)
		{
			va_list kpArg;
			va_start(kpArg,form);

			OvString result;
			if( form && kpArg )
			{
				OvSize	 formed_size = 0;
				formed_size = _vscprintf(form,kpArg)+1;

				result.resize( formed_size );
				vsprintf_s( &result[0], formed_size, form, kpArg);

			}

			va_end(kpArg); 
			return (result);
		}

		OvString replace( const OvString& sentence, const OvString& oldone, const OvString& newone )
		{
			OvVector<OvString> extras;
			OvString target = sentence;
			while ( ! target.empty() )
			{
				extras.push_back( OU::string::split( target, oldone ) );
			}

			for each ( const OvString& val in extras )
			{
				target += val + newone;
			}
			return target;
		}

	}
}