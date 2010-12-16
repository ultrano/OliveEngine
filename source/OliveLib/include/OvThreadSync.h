#pragma once
#include <windows.h>
typedef CRITICAL_SECTION				OvSectionKey;
#define	OvInitSection(__section_key)	::InitializeCriticalSection(&(__section_key))
#define OvDeleteSection(__section_key)	::DeleteCriticalSection(&(__section_key))
#define OvLockSection(__section_key)	::EnterCriticalSection(&(__section_key))
#define OvUnlockSection(__section_key)	::LeaveCriticalSection(&(__section_key))
#define OvAutoLockSection()				OvSectionLocker	__kh_auto_lock_Section__

class OvAutoSectionLocker
{
public:
	OvAutoSectionLocker()
	{
		OvInitSection(m_qSectionKey);
		OvLockSection(m_qSectionKey);
	}
	~OvAutoSectionLocker()
	{
		OvUnlockSection(m_qSectionKey);
		OvDeleteSection(m_qSectionKey);
	}
private:
	OvSectionKey	m_qSectionKey;
};

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
	void Enter(){ ::EnterCriticalSection( &m_section); };
	void Leave(){ ::LeaveCriticalSection( &m_section); };
	CRITICAL_SECTION m_section;
};

class OvSectionGuardian
{
private:
	OvSectionGuardian();
public:
	OvSectionGuardian( OvCriticalSection& critical_section )
		: m_critical_section( critical_section.m_section )
	{
		::EnterCriticalSection( &m_critical_section);
	}
	OvSectionGuardian( CRITICAL_SECTION& critical_section )
		: m_critical_section( critical_section )
	{
		::EnterCriticalSection( &m_critical_section);
	}
	~OvSectionGuardian()
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
	static void	Enter() { __msh_sesstion_key.Enter(); };
	static void	Leave() { __msh_sesstion_key.Leave(); };
private:
	static OvCriticalSection	__msh_sesstion_key;
};

template<typename T>
OvCriticalSection OvThreadSyncer<T>::__msh_sesstion_key;
