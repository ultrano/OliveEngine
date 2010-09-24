#include "OvPropertyBag.h"
#include "OvPropAccesserNode.h"

OvPropertyBag::~OvPropertyBag()
{
	OvPropAccesserNode* kpDeleteNode = BeginAccessNode();
	OvPropAccesserNode* kpNextNode	= 0;
	while (kpDeleteNode)
	{
		kpNextNode = kpDeleteNode->GetNext();
		delete kpDeleteNode;
		kpDeleteNode = kpNextNode;
	}
}

OvPropAccesserNode*	OvPropertyBag::BeginAccessNode()
{
	return m_pListBegin;
};
OvPropAccesserNode*	OvPropertyBag::EndAccessNode()
{
	OvPropAccesserNode* kpListEnd = m_pListBegin;
	if (kpListEnd)
	{
		while (kpListEnd->GetNext())
		{
			kpListEnd = kpListEnd->GetNext();
		}
	}
	return kpListEnd;
}

OvPropAccesserNode*		OvPropertyBag::AddProperty(OvPropertyAccesser* pProperty)
{
	OvPropAccesserNode* kpNewNode = 0;
	if (pProperty)
	{
		kpNewNode = new OvPropAccesserNode(pProperty);
		OvPropAccesserNode* kpListEnd = EndAccessNode();
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