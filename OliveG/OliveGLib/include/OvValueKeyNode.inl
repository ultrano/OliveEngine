//
//template<typename Type_0>
//OvValueKeyNode<Type_0>::OvValueKeyNode(const	Type_0& crFirstKey,const	Type_0& crSecondKey)
//:m_cFirstKey(crFirstKey)
//,m_cSecondKey(crSecondKey)
//{
//	m_fTickInterval = 0;
//	if (IsHaveBothKey())
//	{
//		Type_0	kFirstKey = GetFirstKey();
//		Type_0	kSecondKey = GetSecondKey();
//		m_fTickInterval = kSecondKey.GetKeyTick() - kFirstKey.GetKeyTick();
//	}
//};