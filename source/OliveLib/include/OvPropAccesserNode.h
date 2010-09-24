#pragma once


class OvPropertyAccesser;

class OvPropAccesserNode
{
public:
	OvPropAccesserNode();
	OvPropAccesserNode(OvPropertyAccesser* pProperty);
	~OvPropAccesserNode();
	OvPropertyAccesser*		GetProperty();
	OvPropAccesserNode*		GetNext();
	void					SetNext(OvPropAccesserNode*);
private:
	OvPropertyAccesser*	m_pProperty;
	OvPropAccesserNode* m_pNext;
};