#include "OvObjectFactory.h"
#include "OvObject.h"
#include "OvXNode.h"

OvSingletonEx_IMPL(OvObjectFactory);

void	OvObjectFactory::Singleton_InitializeProcessing()
{
}
void	OvObjectFactory::Singleton_TerminateProcessing()
{

}

OvObjectSPtr	OvObjectFactory::RuntimeManufacture(const char* pClassName,OvStorage& cStorage)
{
	if (GetInstance()->m_mapManufactures.find(pClassName) != GetInstance()->m_mapManufactures.end())
	{
		return GetInstance()->m_mapManufactures[pClassName](cStorage);
	}
	return NULL;
}