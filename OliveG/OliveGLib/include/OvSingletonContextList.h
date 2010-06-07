#pragma once

#include "OvMemoryMgr.h"
#include "OvObjectFactory.h"
#include "OvObjectManager.h"
#include "OvRenderer.h"
#include "OvShaderManager.h"


#define OvREGISTER_SINGLETON_MEMBER(classname) classname m_##classname;

class OvSingletonContextList
{
	
	OvREGISTER_SINGLETON_MEMBER(OvMemoryMgr);
	OvREGISTER_SINGLETON_MEMBER(OvObjectFactory);
	OvREGISTER_SINGLETON_MEMBER(OvObjectManager);
	OvREGISTER_SINGLETON_MEMBER(OvRenderer);
	OvREGISTER_SINGLETON_MEMBER(OvShaderManager);

	friend class OvSingletonPool;
	OvSingletonContextList(){};
	virtual ~OvSingletonContextList(){};
};