#include "OvSingletonPool.h"
#include "OvSingletonContextList.h"

OvSingletonContextList* OvSingletonPool::sm_pSingletonContextList = NULL;

OvSingletonPool::OvSingletonPool()
{
}
OvSingletonPool::~OvSingletonPool()
{
	ShutDown();
}

void	OvSingletonPool::StartUp()
{
	if (IsPoolStartedUp() == false)
	{
		static OvSingletonPool ksPoolStartupInstance;
		sm_pSingletonContextList = new OvSingletonContextList;
	}
	else
	{
		OvError("[OvSingletonPool::StartUp()]�� �ѹ��� ȣ���ϼž� �մϴ�.");
	}
}
void	OvSingletonPool::ShutDown()
{
	if (sm_pSingletonContextList)
	{
		delete sm_pSingletonContextList;
		sm_pSingletonContextList = NULL;
	}
}
OvBool OvSingletonPool::IsPoolStartedUp()
{
	return ( sm_pSingletonContextList != NULL );
}