//#pragma once
//#include "OvValueKey.h"
//
//template<typename Type_0>
//class OvValueKeyNode : OvMemObject
//{
//private:
//	OvValueKeyNode():m_cFirstKey(Type_0::INVALID_KEY),m_cSecondKey(Type_0::INVALID_KEY){};
//public:
//	typedef OvValueKey<Type_0>	NodeKeyType;
//	static const OvValueKeyNode	INVALID;
//public:
//
//	OvValueKeyNode(const	Type_0& crFirstKey,const	Type_0& crSecondKey);
//
//	float					GetTickInterval(){return m_fTickInterval;};
//	bool					IsHaveBothKey(){return (m_pFirstKey.IsValidKey() && m_pSecondKey.IsValidKey());};
//
//private:
//
//	OvValueKeyNode*	m_pNextNode;
//	NodeKeyType		m_cKey;
//
//};
//
//template<typename Type_0>
//const OvValueKeyNode<Type_0> OvValueKeyNode<Type_0>::INVALID;
//
//#include "OvValueKeyNode.inl"
