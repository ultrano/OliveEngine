#pragma once


class OvProperty;

class OvPropertyNode
{
public:
	OvPropertyNode();
	OvPropertyNode(OvProperty* pProperty);
	~OvPropertyNode();
	OvProperty*		GetProperty();
	void			SetNext(OvPropertyNode*);
	OvPropertyNode*	GetNext();
private:
	OvProperty*		m_pProperty;
	OvPropertyNode* m_pNext;
};