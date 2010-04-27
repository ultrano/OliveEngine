#pragma once


class OvProperty;

class OvPropertyNode
{
public:
	OvPropertyNode():m_pProperty(0),m_pNext(0){};
	OvPropertyNode(OvProperty* pProperty):m_pProperty(pProperty),m_pNext(0){};
	OvProperty*		GetProperty();
	void			SetNext(OvPropertyNode*);
	OvPropertyNode*	GetNext();
private:
	OvProperty*		m_pProperty;
	OvPropertyNode* m_pNext;
};