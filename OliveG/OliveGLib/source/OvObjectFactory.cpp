#include "OvObjectFactory.h"
#include "OvXNode.h"

OvSingletonEx_IMPL(OvObjectFactory);
void OvObjectFactory::Singleton_InitializeProcessing()
{
	m_mapFactoryCallback["OvXNode"] = OvXNode::FactoryCallback;
}
void OvObjectFactory::Singleton_TerminateProcessing()
{

}
OvObjectSPtr	OvObjectFactory::CreateInstance(const string& rClass,OvStorage& rStorage)
{
	tdFactoryCallback::iterator kIter = m_mapFactoryCallback.find(rClass);
	if (kIter != m_mapFactoryCallback.end())
	{
		return (kIter->second)(rStorage);
	}
	return NULL;
}