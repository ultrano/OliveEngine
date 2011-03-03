#include "OvRefBase.h"
#include "OvRefCounter.h"

OvRTTI_IMPL_ROOT(OvRefBase);
OvRefBase::OvRefBase()
: m_reference_counter( OvNew OvRefCounter( this ) )
{
	m_reference_counter->IncWeakCount();
};
OvRefBase::~OvRefBase()
{
	m_reference_counter->DecWeakCount();
// 	if(m_dReferenceCount != 0)
// 	{
// 		OvError(
// 			"Object still shared is forced to delete,check this out man\n"
// 			"[Do not use Funtion'delete' on object using 'reference counting']");
// 		OvAssert( (! (m_dReferenceCount>0 || m_dReferenceCount<0)));
// 	}

};

OvRefCounter*		OvRefBase::GetRefCounter()
{
	return m_reference_counter;
}
