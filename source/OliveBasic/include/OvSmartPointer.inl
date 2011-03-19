
template<typename Type_0>
inline OvSmartPointer<Type_0>::OvSmartPointer():m_pReferenceTarget(NULL)
{};

template<typename Type_0>
template<typename Type_1>
inline OvSmartPointer<Type_0>::OvSmartPointer(const OvSmartPointer<Type_1>& _pointer)
:m_pReferenceTarget(reinterpret_cast<Type_0*>(_pointer.GetRear()))
{
	if (m_pReferenceTarget)
	{
		m_pReferenceTarget->IncRefCount();
	}
}
template<typename Type_0>
inline OvSmartPointer<Type_0>::OvSmartPointer( OvSmartPointer<Type_0>& _pointer)
{
	m_pReferenceTarget = _pointer.m_pReferenceTarget;
	if (m_pReferenceTarget)
	{
		m_pReferenceTarget->IncRefCount();
	}
};
template<typename Type_0>
inline OvSmartPointer<Type_0>::OvSmartPointer(const OvSmartPointer<Type_0>& _pointer)
{
	m_pReferenceTarget = _pointer.m_pReferenceTarget;
	if (m_pReferenceTarget)
	{
		m_pReferenceTarget->IncRefCount();
	}
};

template<typename Type_0>
inline OvSmartPointer<Type_0>::OvSmartPointer(Type_0* _pt)
{
	m_pReferenceTarget = _pt;
	if (m_pReferenceTarget)
	{
		m_pReferenceTarget->IncRefCount();
	}
}

template<typename Type_0>
inline OvSmartPointer<Type_0>::~OvSmartPointer()
{
	if(m_pReferenceTarget)
	m_pReferenceTarget->DecRefCount();
}
template<typename Type_0>
inline Type_0* OvSmartPointer<Type_0>::GetRear()const
{
	return (Type_0*)m_pReferenceTarget;
}
template<typename Type_0>
OvSmartPointer<Type_0>::operator OvInt()const
{
	return OvInt(m_pReferenceTarget);
}
template<typename Type_0>
inline Type_0*					OvSmartPointer<Type_0>::operator ->()const
{
	if(!m_pReferenceTarget)
		OvError("NULL에대한 접근 경고:OvSmartPointer이 NULL을 읽으려 합니다.");

	return m_pReferenceTarget;
}
template<typename Type_0>
inline OvSmartPointer<Type_0>&	OvSmartPointer<Type_0>::operator = ( Type_0* _pt)
{
	if (m_pReferenceTarget)
	{
		m_pReferenceTarget->DecRefCount();
	}

	m_pReferenceTarget = _pt;

	if (m_pReferenceTarget)
	{
		m_pReferenceTarget->IncRefCount();
	}

	return *this;
}

template<typename Type_0>
Type_0&							OvSmartPointer<Type_0>::operator [](OvInt _ArrayCount)
{
	return m_pReferenceTarget[_ArrayCount];
};
template<typename Type_0>
inline OvSmartPointer<Type_0>&	OvSmartPointer<Type_0>::operator = ( OvSmartPointer<Type_0>& _copy)
{
	if (m_pReferenceTarget)
	{
		m_pReferenceTarget->DecRefCount();
	}
	m_pReferenceTarget = _copy.m_pReferenceTarget;
	if (m_pReferenceTarget)
	{
		m_pReferenceTarget->IncRefCount();
	}
	return *this;
}
template<typename Type_0>
inline OvSmartPointer<Type_0>&	OvSmartPointer<Type_0>::operator = (const OvSmartPointer<Type_0>& _copy)
{
	if (m_pReferenceTarget)
	{
		m_pReferenceTarget->DecRefCount();
	}
	m_pReferenceTarget = _copy.m_pReferenceTarget;
	if (m_pReferenceTarget)
	{
		m_pReferenceTarget->IncRefCount();
	}
	return *this;
}
template<typename Type_0>
template<typename Type_1>
OvSmartPointer<Type_0>&		OvSmartPointer<Type_0>::operator = (const OvSmartPointer<Type_1>& _copy)
{
	if (m_pReferenceTarget)
	{
		m_pReferenceTarget->DecRefCount();
	}
	m_pReferenceTarget = reinterpret_cast<Type_0*>(_copy.GetRear());
	if (m_pReferenceTarget)
	{
		m_pReferenceTarget->IncRefCount();
	}
	return *this;
}

template<typename Type_0,typename Type_1>
OvBool	operator == (const OvSmartPointer<Type_0>& _copy0,const OvSmartPointer<Type_1>& _copy1)
{
	return ((void*)_copy0.GetRear() == (void*)_copy1.GetRear());
}
template<typename Type_0,typename Type_1>
OvBool	operator != (const OvSmartPointer<Type_0>& _copy0,const OvSmartPointer<Type_1>& _copy1)
{
	return ((void*)_copy0.GetRear() != (void*)_copy1.GetRear());
}

template<typename Type_0,typename Type_1>
OvBool	operator == (const OvSmartPointer<Type_0>& _copy0,const Type_1* _copy1)
{
	return ((void*)_copy0.GetRear() == (void*)_copy1);
}
template<typename Type_0,typename Type_1>
OvBool	operator != (const OvSmartPointer<Type_0>& _copy0,const Type_1* _copy1)
{
	return ((void*)_copy0.GetRear() != (void*)_copy1);
}

template<typename Type_0,typename Type_1>
OvBool	operator == (const Type_0* _copy0,const OvSmartPointer<Type_1>& _copy1)
{
	return ((void*)_copy0 == (void*)_copy1.GetRear());
}
template<typename Type_0,typename Type_1>
OvBool	operator != (const Type_0* _copy0,const OvSmartPointer<Type_1>& _copy1)
{
	return ((void*)_copy0 != (void*)_copy1.GetRear());
}


template<typename Type_0,typename Type_1>
OvBool	operator == (const OvSmartPointer<Type_0>& _copy0, Type_1* _copy1)
{
	return ((void*)_copy0.GetRear() == (void*)_copy1);
}
template<typename Type_0,typename Type_1>
OvBool	operator != (const OvSmartPointer<Type_0>& _copy0, Type_1* _copy1)
{
	return ((void*)_copy0.GetRear() != (void*)_copy1);
}

template<typename Type_0,typename Type_1>
OvBool	operator == ( Type_0* _copy0,const OvSmartPointer<Type_1>& _copy1)
{
	return ((void*)_copy0 == (void*)_copy1.GetRear());
}
template<typename Type_0,typename Type_1>
OvBool	operator != ( Type_0* _copy0,const OvSmartPointer<Type_1>& _copy1)
{
	return ((void*)_copy0 != (void*)_copy1.GetRear());
}