#include "OvUtility.h"
#include <stdio.h>
#define FORMATTING_LENGTH 1024

OvChar* Formatting(const OvChar* pFormat,va_list pArg)
{
	OvChar* kFormatBuf = NULL;
	size_t kFormatLen = 0;
	kFormatLen = _vscprintf(pFormat,pArg)+1;

	kFormatBuf = new OvChar[kFormatLen];

	memset(kFormatBuf,0,kFormatLen);
	vsprintf_s( kFormatBuf, kFormatLen, pFormat, pArg);

	//m_pBuffer = kFormatBuf;
	return (kFormatBuf);

}

OvString OU::string::format( const OvChar* form, ... )
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
