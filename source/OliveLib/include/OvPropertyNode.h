#pragma once


class OvPropertyAccesser;

class OvPropertyNode
{
public:
	OvPropertyNode();
	OvPropertyNode(OvPropertyAccesser* pProperty);
	~OvPropertyNode();
	OvPropertyAccesser*		GetProperty();
	void			SetNext(OvPropertyNode*);
	OvPropertyNode*	GetNext();
private:
	OvPropertyAccesser*		m_pProperty;
	OvPropertyNode* m_pNext;
};