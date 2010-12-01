//
//
//template<typename Type_0>
//OvUInt OvValueKeyCollector<Type_0>::GetKeyCount()
//{
//	return m_mapKeyTale.size();
//}
//
//template<typename Type_0>
//bool			OvValueKeyCollector<Type_0>::IsValidKeyIndex(OvUInt iIndex)
//{
//	if (iIndex <0 || iIndex >= GetKeyCount())
//	{
//		return false;
//	}
//	return true;
//}
//
//template<typename Type_0>
//bool		OvValueKeyCollector<Type_0>::IsOverlapTickKey(float fTick)
//{
//	return (m_mapKeyTale.find(fTick) != m_mapKeyTale.end());
//}
//
//template<typename Type_0>
//void		OvValueKeyCollector<Type_0>::CollectValueKey(float fTick,const Type_0& crValue)
//{
//	m_mapKeyTale[fTick] = crKey;
//	BuildKeyNode();
//}
//
//template<typename Type_0>
//void		OvValueKeyCollector<Type_0>::BuildKeyNode()
//{
//	SortAccessCash();
//	for (unsigned i=0;i<GetKeyCount() - 1;++i)
//	{
//		SKeyNode	kKeyNode;
//		kKeyNode.pFrontKey = &m_vecKeyArray[i];
//		kKeyNode.pBackKey = &m_vecKeyArray[i + 1];
//		m_vecKeyNodeArray.push_back(kKeyNode);
//	}
//	for (unsigned i=0;i<m_vecKeyNodeArray.size() - 1;++i)
//	{
//		m_vecKeyNodeArray[i].pNextNode = &m_vecKeyNodeArray[i + 1];
//	}
//}
//template<typename Type_0>
//void		OvValueKeyCollector<Type_0>::SortAccessCash()
//{
//	m_vecKeyArray.clear();
//	map<float,ContainKeyType>::iterator	kIter = m_mapKeyTale.begin();
//	for ( ; kIter != m_mapKeyTale.end() ; ++kIter)
//	{
//		m_vecKeyArray.push_back(kIter->second);
//	}
//}