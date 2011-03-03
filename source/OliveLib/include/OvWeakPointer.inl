#include "OvRefCounter.h"

template<typename Type_0>
inline OvWeakPointer<Type_0>::OvWeakPointer():m_ref_target(NULL)
{};

template<typename Type_0>
template<typename Type_1>
inline OvWeakPointer<Type_0>::OvWeakPointer(const OvWeakPointer<Type_1>& _pointer)
:m_ref_target(reinterpret_cast<Type_0*>(_pointer.GetRear()))
{
	if (m_ref_target)
	{
		m_ref_target->GetRefCounter()->IncWeakCount();
	}
}
template<typename Type_0>
inline OvWeakPointer<Type_0>::OvWeakPointer( OvWeakPointer<Type_0>& _pointer)
{
	m_ref_target = _pointer.m_ref_target;
	if (m_ref_target)
	{
		m_ref_target->GetRefCounter()->IncWeakCount();
	}
};
template<typename Type_0>
inline OvWeakPointer<Type_0>::OvWeakPointer(const OvWeakPointer<Type_0>& _pointer)
{
	m_ref_target = _pointer.m_ref_target;
	if (m_ref_target)
	{
		m_ref_target->GetRefCounter()->IncWeakCount();
	}
};

//////////////////////////////////////////////////////////////////////////

template<typename Type_0>
template<typename Type_1>
inline OvWeakPointer<Type_0>::OvWeakPointer(const OvSmartPointer<Type_1>& _pointer)
:m_ref_target(reinterpret_cast<Type_0*>(_pointer.GetRear()))
{
	if (m_ref_target)
	{
		m_ref_target->GetRefCounter()->IncWeakCount();
	}
};
template<typename Type_0>
inline OvWeakPointer<Type_0>::OvWeakPointer( OvSmartPointer<Type_0>& _pointer)
:m_ref_target(reinterpret_cast<Type_0*>(_pointer.GetRear()))
{
	if (m_ref_target)
	{
		m_ref_target->GetRefCounter()->IncWeakCount();
	}
};
template<typename Type_0>
inline OvWeakPointer<Type_0>::OvWeakPointer(const OvSmartPointer<Type_0>& _pointer)
:m_ref_target(reinterpret_cast<Type_0*>(_pointer.GetRear()))
{
	if (m_ref_target)
	{
		m_ref_target->GetRefCounter()->IncWeakCount();
	}
};
//////////////////////////////////////////////////////////////////////////

template<typename Type_0>
inline OvWeakPointer<Type_0>::OvWeakPointer(Type_0* _pt)
{
	m_ref_target = _pt;
	if (m_ref_target)
	{
		m_ref_target->GetRefCounter()->IncWeakCount();
	}
}

template<typename Type_0>
inline OvWeakPointer<Type_0>::~OvWeakPointer()
{
	if(m_ref_target)
		m_ref_target->GetRefCounter()->DecWeakCount();
}
template<typename Type_0>
inline Type_0* OvWeakPointer<Type_0>::GetRear()const
{
	return (Type_0*)m_ref_target;
}

template<typename Type_0>
inline OvBool OvWeakPointer<Type_0>::Expired()
{
	if ( m_ref_target )
	{
		return m_ref_target->GetRefCounter()->Expired();
	}
	return true;
}

template<typename Type_0>
OvWeakPointer<Type_0>::operator OvInt()const
{
	return OvInt(m_ref_target);
}
template<typename Type_0>
inline Type_0*					OvWeakPointer<Type_0>::operator ->()const
{
	if(!m_ref_target)
		OvError("NULL에대한 접근 경고:OvWeakPointer이 NULL을 읽으려 합니다.");

	return m_ref_target;
}
template<typename Type_0>
inline OvWeakPointer<Type_0>&	OvWeakPointer<Type_0>::operator = ( Type_0* _pt)
{
	if (m_ref_target)
	{
		m_ref_target->GetRefCounter()->DecWeakCount();
	}

	m_ref_target = _pt;

	if (m_ref_target)
	{
		m_ref_target->GetRefCounter()->IncWeakCount();
	}

	return *this;
}

template<typename Type_0>
Type_0&							OvWeakPointer<Type_0>::operator [](OvInt _ArrayCount)
{
	return m_ref_target[_ArrayCount];
};
template<typename Type_0>
inline OvWeakPointer<Type_0>&	OvWeakPointer<Type_0>::operator = ( OvWeakPointer<Type_0>& _copy)
{
	if (m_ref_target)
	{
		m_ref_target->GetRefCounter()->DecWeakCount();
	}
	m_ref_target = _copy.m_ref_target;
	if (m_ref_target)
	{
		m_ref_target->GetRefCounter()->IncWeakCount();
	}
	return *this;
}
template<typename Type_0>
inline OvWeakPointer<Type_0>&	OvWeakPointer<Type_0>::operator = (const OvWeakPointer<Type_0>& _copy)
{
	if (m_ref_target)
	{
		m_ref_target->GetRefCounter()->DecWeakCount();
	}
	m_ref_target = _copy.m_ref_target;
	if (m_ref_target)
	{
		m_ref_target->GetRefCounter()->IncWeakCount();
	}
	return *this;
}
template<typename Type_0>
template<typename Type_1>
OvWeakPointer<Type_0>&		OvWeakPointer<Type_0>::operator = (const OvWeakPointer<Type_1>& _copy)
{
	if (m_ref_target)
	{
		m_ref_target->GetRefCounter()->DecWeakCount();
	}
	m_ref_target = reinterpret_cast<Type_0*>(_copy.GetRear());
	if (m_ref_target)
	{
		m_ref_target->GetRefCounter()->IncWeakCount();
	}
	return *this;
}
//////////////////////////////////////////////////////////////////////////

template<typename Type_0>
inline OvWeakPointer<Type_0>&	OvWeakPointer<Type_0>::operator = ( OvSmartPointer<Type_0>& _copy)
{
	m_ref_target = _copy.GetRear();
	if (m_ref_target)
	{
		m_ref_target->GetRefCounter()->IncWeakCount();
	}
	return *this;
}
template<typename Type_0>
inline OvWeakPointer<Type_0>&	OvWeakPointer<Type_0>::operator = (const OvSmartPointer<Type_0>& _copy)
{
	m_ref_target = _copy.GetRear();
	if (m_ref_target)
	{
		m_ref_target->GetRefCounter()->IncWeakCount();
	}
	return *this;
}
template<typename Type_0>
template<typename Type_1>
OvWeakPointer<Type_0>&		OvWeakPointer<Type_0>::operator = (const OvSmartPointer<Type_1>& _copy)
{
	m_ref_target = reinterpret_cast<Type_0*>(_copy.GetRear());
	if (m_ref_target)
	{
		m_ref_target->GetRefCounter()->IncWeakCount();
	}
	return *this;
}
//////////////////////////////////////////////////////////////////////////
template<typename Type_0,typename Type_1>
OvBool	operator == (const OvWeakPointer<Type_0>& _copy0,const OvWeakPointer<Type_1>& _copy1)
{
	return ((void*)_copy0.GetRear() == (void*)_copy1.GetRear());
}
template<typename Type_0,typename Type_1>
OvBool	operator != (const OvWeakPointer<Type_0>& _copy0,const OvWeakPointer<Type_1>& _copy1)
{
	return ((void*)_copy0.GetRear() != (void*)_copy1.GetRear());
}

template<typename Type_0,typename Type_1>
OvBool	operator == (const OvWeakPointer<Type_0>& _copy0,const Type_1* _copy1)
{
	return ((void*)_copy0.GetRear() == (void*)_copy1);
}
template<typename Type_0,typename Type_1>
OvBool	operator != (const OvWeakPointer<Type_0>& _copy0,const Type_1* _copy1)
{
	return ((void*)_copy0.GetRear() != (void*)_copy1);
}

template<typename Type_0,typename Type_1>
OvBool	operator == (const Type_0* _copy0,const OvWeakPointer<Type_1>& _copy1)
{
	return ((void*)_copy0 == (void*)_copy1.GetRear());
}
template<typename Type_0,typename Type_1>
OvBool	operator != (const Type_0* _copy0,const OvWeakPointer<Type_1>& _copy1)
{
	return ((void*)_copy0 != (void*)_copy1.GetRear());
}


template<typename Type_0,typename Type_1>
OvBool	operator == (const OvWeakPointer<Type_0>& _copy0, Type_1* _copy1)
{
	return ((void*)_copy0.GetRear() == (void*)_copy1);
}
template<typename Type_0,typename Type_1>
OvBool	operator != (const OvWeakPointer<Type_0>& _copy0, Type_1* _copy1)
{
	return ((void*)_copy0.GetRear() != (void*)_copy1);
}

template<typename Type_0,typename Type_1>
OvBool	operator == ( Type_0* _copy0,const OvWeakPointer<Type_1>& _copy1)
{
	return ((void*)_copy0 == (void*)_copy1.GetRear());
}
template<typename Type_0,typename Type_1>
OvBool	operator != ( Type_0* _copy0,const OvWeakPointer<Type_1>& _copy1)
{
	return ((void*)_copy0 != (void*)_copy1.GetRear());
}