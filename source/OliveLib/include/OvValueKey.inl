
template<typename Type_0>
OvValueKey<Type_0>::OvValueKey(const OvValueKey<Type_0>& crKey):m_fTickTime(crKey.GetKeyTick())
{
	m_pKeyValue = NULL;
	unsigned int	kiTypeSize = sizeof(Type_0);
	byte*	kpTypeStore = new byte[kiTypeSize];
	CopyMemory(kpTypeStore,&crKey.GetKeyValue(),kiTypeSize);
	m_pKeyValue = kpTypeStore;
};

template<typename Type_0>
OvValueKey<Type_0>::OvValueKey(float fTick,const Type_0& crValue):m_fTickTime(fTick)
{
	m_pKeyValue = NULL;
	unsigned int	kiTypeSize = sizeof(Type_0);
	byte*	kpTypeStore = new byte[kiTypeSize];
	CopyMemory(kpTypeStore,&crValue,kiTypeSize);
	m_pKeyValue = kpTypeStore;
};