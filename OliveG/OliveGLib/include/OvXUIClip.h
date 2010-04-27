#pragma once
#include "OvXNode.h"
#include "OvUserInterface.h"
class OvXUIClip : public OvXNode, public OvUserInterface
{
	OvRTTI_DECL(OvXUIClip);

private:

	//! Member Values (Ensconsed for encapsulation)
	//! Application can access member only using get,set interface
	struct OvPimple;
	OvAutoPtr< OvPimple> m_pPimple;
};