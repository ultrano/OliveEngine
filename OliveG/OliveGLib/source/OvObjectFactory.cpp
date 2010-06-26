#include "OvObjectFactory.h"
#include "OvXNode.h"

OvObjectFactory::OvObjectFactory()
{
	m_mapFactoryCallback["OvXNode"] = OvXNode::FactoryCallback;
}
OvObjectFactory::~OvObjectFactory()
{

}
OvObjectSPtr	OvObjectFactory::CreateInstance(const string& rClass,OvObjectID& objID)
{
	tdFactoryCallback::iterator kIter = m_mapFactoryCallback.find(rClass);
	if (kIter != m_mapFactoryCallback.end())
	{
		return (kIter->second)(objID);
	}
	return NULL;
}