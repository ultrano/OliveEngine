#include "OvStringUtility.h"
#include <stdio.h>
#define FORMATTING_LENGTH 1024

OvArrayAutoPtr<OvChar> FormatString(const OvChar* _pFormat,...)
{
	if(!_pFormat)
		return NULL;

	va_list kpArg;
	va_start(kpArg,_pFormat);

	OvChar* kFormatBuf = NULL;
	size_t kFormatLen = 0;

	if(kpArg)
	{

		kFormatLen = _vscprintf(_pFormat,kpArg)+1;

		kFormatBuf = new OvChar[kFormatLen];

		memset(kFormatBuf,0,kFormatLen);
		vsprintf_s( kFormatBuf, kFormatLen, _pFormat, kpArg);

	}

	va_end(kpArg); 
	return (kFormatBuf);

}


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

OvFormatString::OvFormatString()
:m_pBuffer(NULL)
{

};

OvFormatString::OvFormatString(const OvChar* _pFormat,...):m_pBuffer(NULL)
{
	if(!_pFormat)
		return ;

	//! if it has buffer, release that.
	if (m_pBuffer)
		OvArrayAutoPtr<OvChar> kpLocal = m_pBuffer;

	va_list kpArg;
	va_start(kpArg,_pFormat);

	m_pBuffer = Formatting(_pFormat,kpArg);

	va_end(kpArg); 
}
OvChar* OvFormatString::operator()(const OvChar* _pFormat,...)
{
	if(!_pFormat)
		return NULL;

	// 지역 변수인 오토피티알에 넣어 자동 삭제를 유도한다.
	if (m_pBuffer)
		OvArrayAutoPtr<OvChar> kpLocal = m_pBuffer;

	va_list kpArg;
	va_start(kpArg,_pFormat);

	m_pBuffer = Formatting(_pFormat,kpArg);

	va_end(kpArg); 
	return m_pBuffer.GetRear();

}
OvFormatString::operator OvChar*()
{
	return m_pBuffer.GetRear();
}