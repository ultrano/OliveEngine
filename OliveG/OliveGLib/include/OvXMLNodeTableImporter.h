#pragma once
#include "OvMemObject.h"
#include "OvAutoPtr.h"

class OvXMLNodeTableImporter : OvMemObject
{

private:
	struct OvPimple;
	OvAutoPtr<OvPimple> m_pPimple;
};