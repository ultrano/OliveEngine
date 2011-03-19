#include "OvOlive.h"

#include "OvMemoryMgr.h"
#include "OvObjectManager.h"

void OvOlive::StartUp()
{
	OvMemoryMgr::GetInstance();
	OvObjectManager::GetInstance();
}

void OvOlive::ShutDown()
{

}
