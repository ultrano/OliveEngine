#pragma once
#include "OvMemObject.h"
#include "OvTypeDef.h"
#include <windows.h>

class OvThread : public OvMemObject
{
public:

	typedef void (*FuncType)(void*);

public:

	OvThread( const OvString& name );
	OvThread( const OvString& name, FuncType func );
	~OvThread();

	void		Start();
	void		Suspend();
	void		Resume();

	virtual void Run();

private:
	HANDLE		m_thread;
	FuncType	m_func;
};