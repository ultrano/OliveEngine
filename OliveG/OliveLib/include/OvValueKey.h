#pragma once
#include "OvMemObject.h"
#include "OvAutoPtr.h"

template<typename Type_0>
class OvValueKey : OvMemObject
{
public:
	
	static const OvValueKey	INVALID_KEY;

public:

	OvValueKey():m_fTickTime(-1),m_pKeyValue(NULL){};
	OvValueKey(const OvValueKey<Type_0>& crKey);
	OvValueKey(float fTick,const Type_0& crValue);

	float	GetKeyTick(){return m_fTickTime;};
	Type_0	GetKeyValue(){return *((Type_0*)m_pKeyValue.GetRear());};

	bool	IsValidKey(){return ((this) != &INVALID_KEY)};

private:

	float				m_fTickTime;
	OvAutoPtr<byte*>	m_pKeyValue;

};
template<typename Type_0>
const OvValueKey<Type_0> OvValueKey<Type_0>::INVALID_KEY;
#include "OvValueKey.inl"