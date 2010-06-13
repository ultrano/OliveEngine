#include "OvPropertyBag.h"
#include "OvPropertyNode.h"

OvPropertyBag::~OvPropertyBag()
{
	OvPropertyNode* kpDeleteNode = BeginProperty();
	OvPropertyNode* kpNextNode	= 0;
	while (kpDeleteNode)
	{
		kpNextNode = kpDeleteNode->GetNext();
		delete kpDeleteNode;
		kpDeleteNode = kpNextNode;
	}
}

OvPropertyNode*	OvPropertyBag::BeginProperty()
{
	return m_pListBegin;
};
OvPropertyNode*	OvPropertyBag::EndProperty()
{
	OvPropertyNode* kpListEnd = m_pListBegin;
	if (kpListEnd)
	{
		while (kpListEnd->GetNext())
		{
			kpListEnd = kpListEnd->GetNext();
		}
	}
	return kpListEnd;
}

OvPropertyNode*		OvPropertyBag::AddProperty(OvProperty* pProperty)
{
	OvPropertyNode* kpNewNode = 0;
	if (pProperty)
	{
		kpNewNode = new OvPropertyNode(pProperty);
		OvPropertyNode* kpListEnd = EndProperty();
		if (kpNewNode && kpListEnd)
		{
			kpListEnd->SetNext(kpNewNode);
		}
		else
		{
			m_pListBegin = kpNewNode;
		}
	}
	return kpNewNode;
}