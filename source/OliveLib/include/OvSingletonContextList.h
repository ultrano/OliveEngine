#pragma once

#include "OvMemoryMgr.h"
#include "OvObjectFactory.h"
#include "OvObjectManager.h"
#include "OvRenderer.h"
#include "OvResourceManager.h"
#include "OvShaderManager.h"
#include "OvMessageManager.h"
#include "OvInputManager.h"
#include "OvThreadManager.h"

#define OvREGISTER_SINGLETON_MEMBER(classname) classname m_##classname;

class OvSingletonContextList
{
	
	OvREGISTER_SINGLETON_MEMBER(OvMemoryMgr);
	OvREGISTER_SINGLETON_MEMBER(OvObjectManager);
	OvREGISTER_SINGLETON_MEMBER(OvMessageManager);
	OvREGISTER_SINGLETON_MEMBER(OvInputManager);
	OvREGISTER_SINGLETON_MEMBER(OvRenderer);
	OvREGISTER_SINGLETON_MEMBER(OvResourceManager);
	OvREGISTER_SINGLETON_MEMBER(OvShaderManager);
	OvREGISTER_SINGLETON_MEMBER(OvThreadManager);
	
	

	friend class OvSingletonPool;
	OvSingletonContextList(){};
	virtual ~OvSingletonContextList(){};
};