#include "OliveDevice.h"
#include "OvSingleton.h"
#include "OvSingletonContextList.h"

void OliveDevice::EngineOn()
{
	OvSingletonPool::StartUp();
	OvRenderer::GetInstance()->_generate_renderer();
	OvInputManager::GetInstance()->_initialize( OvRenderer::GetInstance()->GetWindowHandle() );
}

void OliveDevice::EngineOff()
{
	OvSingletonPool::ShutDown();
}

OvBool OliveDevice::Run()
{
	OvInputManager::GetInstance()->_update();
	OvMessageManager::GetInstance()->_update();

	return OvMessageManager::GetInstance()->IsWindowAlive();
}