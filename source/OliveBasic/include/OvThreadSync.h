#pragma once
#include <windows.h>

class OvCriticalSection
{
public:
	OvCriticalSection()
	{
		InitializeCriticalSection( &m_section );
	}
	~OvCriticalSection()
	{
		DeleteCriticalSection( &m_section );
	}
	void Lock(){ ::EnterCriticalSection( &m_section); };
	void Unlock(){ ::LeaveCriticalSection( &m_section); };
	CRITICAL_SECTION m_section;
};

class OvAutoSection
{
private:
	OvAutoSection();
public:
	OvAutoSection( OvCriticalSection& critical_section )
		: m_critical_section( critical_section.m_section )
	{
		::EnterCriticalSection( &m_critical_section);
	}
	OvAutoSection( CRITICAL_SECTION& critical_section )
		: m_critical_section( critical_section )
	{
		::EnterCriticalSection( &m_critical_section);
	}
	~OvAutoSection()
	{
		::LeaveCriticalSection( &m_critical_section);
	}
private:
	CRITICAL_SECTION&	m_critical_section;
};
template<typename T>
class	OvThreadSyncer
{
public:
	struct OvSectionLock 
	{
		OvSectionLock() { OvThreadSyncer<T>::Enter(); }
		~OvSectionLock() { OvThreadSyncer<T>::Leave(); }
	};
	static void	Enter() { __msh_sesstion_key.Lock(); };
	static void	Leave() { __msh_sesstion_key.Unlock(); };
private:
	static OvCriticalSection	__msh_sesstion_key;
};

template<typename T>
OvCriticalSection OvThreadSyncer<T>::__msh_sesstion_key;
