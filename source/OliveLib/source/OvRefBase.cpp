
#include "OvRefBase.h"
OvRTTI_IMPL_ROOT(OvRefBase);
OvRefBase::OvRefBase():m_dReferenceCount(0)
{
	//OvInitSection(m_qSectionKey);
};
OvRefBase::~OvRefBase()
{
	if(m_dReferenceCount != 0)
	{
		OvAssertMsg(
			"Object still shared is forced to delete,check this out man\n"
			"[Do not use Funtion'delete' on object using 'reference counting']");
		OvAssert( (! (m_dReferenceCount>0 || m_dReferenceCount<0)));
	}

	//OvDeleteSection(m_qSectionKey);
};
OvInt		OvRefBase::IncreaseReferenceCount()
{
	//OvTargetSectionLocker kLocker(m_qSectionKey);
	++m_dReferenceCount;
	return m_dReferenceCount;
}
OvInt		OvRefBase::DecreaseReferenceCount()
{
	//OvTargetSectionLocker kLocker(m_qSectionKey);
	--m_dReferenceCount;
	if (m_dReferenceCount <= 0)
	{
		// 요기서 삭제;
		DeleteThis();
		m_dReferenceCount = 0;
	}
	return m_dReferenceCount;
}


OvInt		OvRefBase::GetReferenceCount()
{
	//OvTargetSectionLocker kLocker(m_qSectionKey);
	return m_dReferenceCount;
}

void	OvRefBase::ForcedDeleteThis()
{
	m_dReferenceCount = 0;
	DeleteThis();
}