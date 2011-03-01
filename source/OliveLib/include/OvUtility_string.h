#pragma once
#include "OvTypeDef.h"

namespace OU
{
	// √‚√≥ : http://www.gammon.com.au/forum/bbshowpost.php?bbsubject_id=2896

	namespace string
	{
#define SPACES " \t\r\n"
		OvString trim_right (const OvString & s, const OvString & t = SPACES);
		OvString trim_left (const OvString & s, const OvString & t = SPACES);
		OvString trim (const OvString & s, const OvString & t = SPACES);
		OvString split ( OvString & s, const OvString & delim = " ", const bool trim_spaces = true);
		OvString format( const OvChar* form, ...);

		OvString replace( const OvString& sentence, const OvString& oldone, const OvString& newone );

	}
}