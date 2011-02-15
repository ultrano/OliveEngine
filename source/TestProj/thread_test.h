
#include "include_header.h"
#include "OvThread.h"
#include "OliveDevice.h"
#include "OvThreadManager.h"

void func0(void*)
{
	while(1) OutputDebugString("00000000000000\n");
}
void func1(void*)
{
	while(1) OutputDebugString("11111111111111\n");
}

GL_TEST_CASE_FUNC( thread_test )
{

	OliveDevice::EngineOn();
	{
		OvThreadManager * task = OvThreadManager::GetInstance();
		OvThread thread0( "thread0", func0 );
		OvThread thread1( "thread1", func1 );
		thread0.Start();
		thread1.Start();
		while (1)
		{
		}
	}
	OliveDevice::EngineOff();
}