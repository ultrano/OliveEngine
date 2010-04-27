#pragma once

#include "OvRenderableObject.h"
#include "OvUserInterface.h"

class OvXUIObject : public OvRenderableObject, public OvUserInterface
{
	OvRTTI_DECL(OvXUIObject);

private:



	//! Member Values (Ensconsed for encapsulation)
	//! Application can access member only using get,set interface
	struct OvPimple;
	OvAutoPtr< OvPimple> m_pPimple;
};