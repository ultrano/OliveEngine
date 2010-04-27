#pragma once

class OvSingletonContextList;

class OvSingletonPool
{
public:

	OvSingletonPool();
	~OvSingletonPool();

	static void	StartUp();
	static void	ShutDown();
	static bool IsPoolStartedUp();

private:

	static OvSingletonContextList* sm_pSingletonContextList;

};