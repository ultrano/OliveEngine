#include "OvStringUtility.h"
#include <stdio.h>
#define FORMATTING_LENGTH 1024

OvArrayAutoPtr<char> FormatString(const char* _pFormat,...)
{
	if(!_pFormat)
		return NULL;

	va_list kpArg;
	va_start(kpArg,_pFormat);

	char* kFormatBuf = NULL;
	size_t kFormatLen = 0;

	if(kpArg)
	{

		kFormatLen = _vscprintf(_pFormat,kpArg)+1;

		kFormatBuf = new char[kFormatLen];

		memset(kFormatBuf,0,kFormatLen);
		vsprintf_s( kFormatBuf, kFormatLen, _pFormat, kpArg);

	}

	va_end(kpArg); 
	return (kFormatBuf);

}


char* Formatting(const char* pFormat,va_list pArg)
{
	char* kFormatBuf = NULL;
	size_t kFormatLen = 0;
	kFormatLen = _vscprintf(pFormat,pArg)+1;

	kFormatBuf = new char[kFormatLen];

	memset(kFormatBuf,0,kFormatLen);
	vsprintf_s( kFormatBuf, kFormatLen, pFormat, pArg);

	//m_pBuffer = kFormatBuf;
	return (kFormatBuf);

}

OvFormatString::OvFormatString()
:m_pBuffer(NULL)
{

};

OvFormatString::OvFormatString(const char* _pFormat,...):m_pBuffer(NULL)
{
	if(!_pFormat)
		return ;

	//! if it has buffer, release that.
	if (m_pBuffer)
		OvArrayAutoPtr<char> kpLocal = m_pBuffer;

	va_list kpArg;
	va_start(kpArg,_pFormat);

	m_pBuffer = Formatting(_pFormat,kpArg);

	va_end(kpArg); 
}
char* OvFormatString::operator()(const char* _pFormat,...)
{
	if(!_pFormat)
		return NULL;

	// ���� ������ ������Ƽ�˿� �־� �ڵ� ������ �����Ѵ�.
	if (m_pBuffer)
		OvArrayAutoPtr<char> kpLocal = m_pBuffer;

	va_list kpArg;
	va_start(kpArg,_pFormat);

	m_pBuffer = Formatting(_pFormat,kpArg);

	va_end(kpArg); 
	return m_pBuffer.GetRear();

}
OvFormatString::operator char*()
{
	return m_pBuffer.GetRear();
}