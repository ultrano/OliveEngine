#pragma once
class OvStoreObject;
namespace OvXmlUtility
{

	bool SaveStoreToXml(OvStoreObject* pObj);
	OvStoreObject* LoadXmlToStore();
}
namespace OXU = OvXmlUtility;