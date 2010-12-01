//#pragma once
//#include "OvValueKey.h"
//#include <vector>
//#include <map>
//
//template<typename Type_0>
//class OvValueKeyCollector : OvMemObject
//{
//public:
//	typedef OvValueKey<Type_0>	ContainKeyType;
//	struct SKeyNode : OvMemObject
//	{
//		SKeyNode():pNextNode(NULL),pFrontKey(NULL),pBackKey(NULL){};
//		SKeyNode*		pNextNode;
//		ContainKeyType*	pFrontKey;
//		ContainKeyType*	pBackKey;
//	};
//public:
//
//	OvBool			IsValidKeyIndex(OvUInt iIndex);
//	OvBool			IsOverlapTickKey(float fTick);
//
//	void			CollectValueKey(float fTick,const Type_0& crValue);
//	void			BuildKeyNode();
//	void			SortAccessCash();
//
//	OvUInt	GetKeyCount();
//	ContainKeyType	GetKeyAt(OvUInt iIndex)
//	{
//		if (IsValidKeyIndex(iIndex))
//			return m_vecKeyArray[iIndex];
//		return ContainKeyType::INVALID_KEY;
//	};
//
//private:
//	map<float,ContainKeyType>	m_mapKeyTale;
//	vector<ContainKeyType>		m_vecKeyArray;
//	vector<SKeyNode>			m_vecKeyNodeArray;
//};
//#include "OvValueKeyCollector.inl"