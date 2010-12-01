#pragma once
#include "OvTypeDef.h"

class OvSingletonContextList;

class OvSingletonPool
{
public:

	OvSingletonPool();
	~OvSingletonPool();

	static void	StartUp();
	static void	ShutDown();
	static OvBool IsPoolStartedUp();

private:

	static OvSingletonContextList* sm_pSingletonContextList;

};