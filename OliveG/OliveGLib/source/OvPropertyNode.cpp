#include "OvPropertyNode.h"



OvProperty*		OvPropertyNode::GetProperty()
{
	return m_pProperty;
}
void			OvPropertyNode::SetNext(OvPropertyNode* pNext)
{
	m_pNext = pNext;
}
OvPropertyNode*	OvPropertyNode::GetNext()
{
	return m_pNext;
}