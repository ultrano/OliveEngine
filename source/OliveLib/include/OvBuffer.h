#pragma once
#include "OvRefBase.h"
#include "OvAutoPtr.h"
#include "OvBufferInputStream.h"
#include "OvBufferOutputStream.h"

OvREF_POINTER(OvBuffer);
class OvBuffer : public OvRefBase
{
public:

	enum { DEFAULT_BUFFER_INCREMENT = 64 };

	static OvBufferSPtr CreateBuffer( OvSize capacity, OvSize increment = DEFAULT_BUFFER_INCREMENT );

public:

	OvByte *	Pointer();
	OvSize		Size();
	OvSize		Increment();

	void		Establish( OvUInt count = 1 );

private:
	OvBuffer();
private:
	OvArrayAutoPtr<OvByte>	m_buf;
	OvSize					m_size;
	OvSize					m_increment;
};