
#include "OvRefObject.h"
OvRTTI_IMPL_ROOT(OvRefObject);
OvRefObject::OvRefObject():m_ref_count(0)
{
};
OvRefObject::~OvRefObject()
{
	if(m_ref_count != 0)
	{
		OvError(
			"Object still shared is forced to delete,check this out man\n"
			"[Do not use Funtion'delete' on object using 'reference counting']");
		OvAssert( (! (m_ref_count>0 || m_ref_count<0)));
	}

};
OvInt		OvRefObject::IncRefCount()
{
	++m_ref_count;
	return m_ref_count;
}
OvInt		OvRefObject::DecRefCount()
{
	--m_ref_count;
	if (m_ref_count <= 0)
	{
		// 요기서 삭제;
		DeleteThis();
		m_ref_count = 0;
	}
	return m_ref_count;
}


OvInt		OvRefObject::GetRefCount()
{
	return m_ref_count;
}
