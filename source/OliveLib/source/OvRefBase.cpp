
#include "OvRefBase.h"
OvRTTI_IMPL_ROOT(OvRefBase);
OvRefBase::OvRefBase():m_dReferenceCount(0)
{
};
OvRefBase::~OvRefBase()
{
	if(m_dReferenceCount != 0)
	{
		OvError(
			"Object still shared is forced to delete,check this out man\n"
			"[Do not use Funtion'delete' on object using 'reference counting']");
		OvAssert( (! (m_dReferenceCount>0 || m_dReferenceCount<0)));
	}

};
OvInt		OvRefBase::IncreaseReferenceCount()
{
	++m_dReferenceCount;
	return m_dReferenceCount;
}
OvInt		OvRefBase::DecreaseReferenceCount()
{
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
	return m_dReferenceCount;
}

void	OvRefBase::ForcedDeleteThis()
{
	m_dReferenceCount = 0;
	DeleteThis();
}