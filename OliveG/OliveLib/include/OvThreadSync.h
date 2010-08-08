#pragma once

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

class OvTargetSectionLocker
{
public:
	OvTargetSectionLocker(OvSectionKey&	rSectionKey):m_qSectionKey(rSectionKey)
	{
		OvLockSection(m_qSectionKey);
	}
	~OvTargetSectionLocker()
	{
		OvUnlockSection(m_qSectionKey);
	}
private:
	OvSectionKey&	m_qSectionKey;
};
//template<typename Type0>
//class	OvMultiThreadSync
//{
//	friend struct OvSectionLocker;
//public:
//	OvMultiThreadSync()
//	{
//		OvInitSection(Type0::__msh_sesstion_key);
//	}
//	~OvMultiThreadSync()
//	{
//		OvDeleteSection(Type0::__msh_sesstion_key);
//	}
//protected:
//	struct OvSectionLocker 
//	{
//		OvSectionLocker()
//		{
//			OvLockSection(Type0::__msh_sesstion_key);
//		}
//		~OvSectionLocker()
//		{
//			OvUnlockSection(Type0::__msh_sesstion_key);
//		}
//	};
//private:
//	static OvSectionKey	__msh_sesstion_key;
//};
//
//template<typename Type0>
//OvSectionKey OvMultiThreadSync<Type0>::__msh_sesstion_key;
