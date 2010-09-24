#include "OvPropAccesserNode.h"
#include "OvPropertyAccesser.h"

OvPropAccesserNode::OvPropAccesserNode()
:m_pProperty(0)
,m_pNext(0)
{

};

OvPropAccesserNode::OvPropAccesserNode(OvPropertyAccesser* pProperty)
:m_pProperty(pProperty)
,m_pNext(0)
{

};
OvPropAccesserNode::~OvPropAccesserNode()
{
	if (m_pProperty)
	{

		delete m_pProperty;
		m_pProperty = 0;
	}
}

OvPropertyAccesser*		OvPropAccesserNode::GetProperty()
{
	return m_pProperty;
}
void			OvPropAccesserNode::SetNext(OvPropAccesserNode* pNext)
{
	m_pNext = pNext;
}
OvPropAccesserNode*	OvPropAccesserNode::GetNext()
{
	return m_pNext;
}