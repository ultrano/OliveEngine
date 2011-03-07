#pragma once
#include "OvRefObject.h"
#include "OvAutoPtr.h"
#include "OvBufferInputStream.h"
#include "OvBufferOutputStream.h"

OvREF_POINTER(OvBuffer);
class OvBuffer : public OvRefObject
{
	OvRTTI_DECL(OvBuffer);
public:

	enum { 
		DEFAULT_BUFFER_CAPACITY = 256,
		DEFAULT_BUFFER_INCREMENT = 64 
	};

	static OvBufferSPtr CreateBuffer( OvSize capacity = DEFAULT_BUFFER_CAPACITY
									, OvSize increment = DEFAULT_BUFFER_INCREMENT );

public:

	OvByte *	Pointer();
	OvSize		Size();
	OvSize		Increment();

	void		Establish( OvUInt times = 1 );

private:
	OvBuffer();
private:
	OvArrayAutoPtr<OvByte>	m_buf;
	OvSize					m_size;
	OvSize					m_increment;
};