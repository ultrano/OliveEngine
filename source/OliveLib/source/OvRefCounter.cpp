#include "OvRefCounter.h"
#include "OvRefBase.h"

OvRefCounter::OvRefCounter()
: m_ref_count( 0 )
, m_weak_count( 0 )
, m_pointer( NULL )
{

}

OvRefCounter::OvRefCounter( OvRefBase* ptr )
: m_ref_count( 0 )
, m_weak_count( 0 )
, m_pointer( ptr )
{

}

OvRefCounter::~OvRefCounter()
{

}

void OvRefCounter::_delete_this()
{
	delete this;
}

OvUInt OvRefCounter::IncRefCount()
{
	return ++m_ref_count;
}

OvUInt OvRefCounter::DecRefCount()
{
	if ( (--m_ref_count) <= 0 && m_pointer )
	{
		OvRefBase* ptr = m_pointer;
		m_pointer = NULL;
		ptr->DeleteThis();
		return 0;
	}
	return m_ref_count;
}

OvUInt OvRefCounter::IncWeakCount()
{
	return ++m_weak_count;
}

OvUInt OvRefCounter::DecWeakCount()
{
	if ( (--m_weak_count) <= 0)
	{
		_delete_this();
		return 0;
	}
	return m_weak_count;
}

OvBool OvRefCounter::Expired()
{
	return (m_weak_count <= 0 );
}
