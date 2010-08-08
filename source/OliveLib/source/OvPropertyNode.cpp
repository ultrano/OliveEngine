#include "OvPropertyNode.h"
#include "OvProperty.h"

OvPropertyNode::OvPropertyNode()
:m_pProperty(0)
,m_pNext(0)
{

};

OvPropertyNode::OvPropertyNode(OvProperty* pProperty)
:m_pProperty(pProperty)
,m_pNext(0)
{

};
OvPropertyNode::~OvPropertyNode()
{
	if (m_pProperty)
	{

		delete m_pProperty;
		m_pProperty = 0;
	}
}

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