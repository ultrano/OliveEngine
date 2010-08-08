#include "OvXmlUtility.h"
#include "OvStoreObject.h"
#include "OvStoreData.h"
#include "OvStoreNode.h"
#include "tinyxml.h"

using namespace OvXmlUtility;
namespace OvXmlUtility
{

	bool	ConvertStoreObjectToElement(OvStoreObject* pObj, TiXmlNode* rXmlNode);
	//bool	ConvertElementToStoreObject();

	bool	ConvertDataToElement(OvStoreObject* pObj, TiXmlNode* rXmlNode);
	bool	ConvertElementToData(TiXmlNode* rXmlNode, OvStoreObject* pObj);

	bool	ConvertNodeToElement(OvStoreObject* pObj, TiXmlNode* rXmlNode);
	bool	ConvertElementToNode(TiXmlNode* rXmlNode, OvStoreObject* pObj);

}

bool	OXU::ConvertStoreObjectToElement(OvStoreObject* pObj, TiXmlNode* rXmlNode)
{
	if (rXmlNode && pObj)
	{
		bool kbRet = false;
		if ( OvRTTI_Util::IsTypeOf< OvStoreData >( pObj ) )
		{
			kbRet |= ConvertDataToElement(pObj,rXmlNode);
		}
		else if ( OvRTTI_Util::IsTypeOf< OvStoreNode >( pObj ) )
		{
			kbRet |= ConvertNodeToElement(pObj,rXmlNode);
		}
		return kbRet;
	}
	return false;
}

bool	OXU::ConvertDataToElement(OvStoreObject* pObj, TiXmlNode* rXmlNode)
{
	if ( (rXmlNode && pObj) && (OvRTTI_Util::IsTypeOf< OvStoreData >( pObj ) && rXmlNode->ToElement()) )
	{
		TiXmlElement* pElement = rXmlNode->ToElement();
		OvStoreData* pData = (OvStoreData*)pObj;
		TiXmlText		kDataText(pData->GetDataString());

		pElement->SetValue("DATA");
		pElement->SetAttribute("name",pData->GetName());
		pElement->SetAttribute("type",pData->GetDataType());
		pElement->InsertEndChild(kDataText);
		return true;
	}
	return false;
}
bool	OXU::ConvertElementToData(TiXmlNode* rXmlNode, OvStoreObject* pObj)
{
	if ((rXmlNode && pObj) && (OvRTTI_Util::IsTypeOf< OvStoreData >( pObj ) && rXmlNode->ToElement()))
	{
		if (rXmlNode->Value() == "DATA")
		{
			TiXmlElement* pElement = rXmlNode->ToElement();
			OvStoreData* pData = (OvStoreData*)pObj;

			pData->SetName(pElement->Attribute("name"));
			pData->SetDataType(pElement->Attribute("type"));
			pData->SetDataString(pElement->GetText());
			return true;
		}
	}
	return false;
}
bool	OXU::ConvertNodeToElement(OvStoreObject* pObj, TiXmlNode* rXmlNode)
{
	if ((rXmlNode && pObj) && (OvRTTI_Util::IsTypeOf< OvStoreNode >( pObj ) && rXmlNode->ToElement()))
	{
		TiXmlElement* pElement = rXmlNode->ToElement();
		OvStoreNode* pNode = (OvStoreNode*)pObj;

		pElement->SetValue("NODE");
		pElement->SetAttribute("name",pNode->GetName());
		for (unsigned int i = 0 ; i < pNode->ChildCount() ; ++i)
		{
			TiXmlElement kChildElement("Unknown");
			
			ConvertStoreObjectToElement(pNode->ChildAt(i),&kChildElement);

			pElement->InsertEndChild(kChildElement);
		}
		return true;
	}
	return false;
}
bool	OXU::ConvertElementToNode(TiXmlNode* rXmlNode, OvStoreObject* pObj)
{
// 	if ((rXmlNode && pObj) && (OvRTTI_Util::IsTypeOf< OvStoreNode >( pObj ) && rXmlNode->ToElement()))
// 	{
// 		if (rXmlNode->Value() == "NODE")
// 		{
// 			TiXmlElement* pElement = rXmlNode->ToElement();
// 			OvStoreNode* pNode = (OvStoreNode*)pObj;
// 
// 			pNode->SetName(pElement->Attribute("name"));
// 
// 		}
// 	}
	return false;
}

bool InsertElement(TiXmlNode& rXmlNode, OvStoreObject* pObj);
bool InsertStoreNode(TiXmlNode& rXmlNode, OvStoreObject* pObj);
bool InsertStoreData(TiXmlNode& rXmlNode, OvStoreObject* pObj);

bool InsertStoreNode(TiXmlNode& rXmlNode, OvStoreObject* pObj)
{
	if ( OvRTTI_Util::IsTypeOf< OvStoreNode >( pObj ) )
	{
		OvStoreNode* pNode = (OvStoreNode*)pObj;
		
		TiXmlElement	kElement("NODE");

		kElement.SetAttribute("name",pNode->GetName());
		
		for (int i = 0 ; i < pNode->ChildCount() ; ++i)
		{
			OvStoreObject* pChild = pNode->ChildAt(i);
			InsertElement(kElement,pChild);
		}

		rXmlNode.InsertEndChild(kElement);
		
		return true;
	}
	return false;
}

bool InsertStoreData(TiXmlNode& rXmlNode, OvStoreObject* pObj)
{
	if ( OvRTTI_Util::IsTypeOf< OvStoreData >( pObj ) )
	{
		OvStoreData* pData = (OvStoreData*)pObj;
		TiXmlElement	kElement("DATA");
		TiXmlText		kDataText(pData->GetDataString());

		kElement.SetAttribute("name",pData->GetName());
		kElement.SetAttribute("type",pData->GetDataType());
		kElement.InsertEndChild(kDataText);

		rXmlNode.InsertEndChild(kElement);
		return true;
	}
	return false;
}

bool InsertElement(TiXmlNode& rXmlNode, OvStoreObject* pObj)
{
	if ( OvRTTI_Util::IsTypeOf< OvStoreData >( pObj ) )
	{
		return InsertStoreData(rXmlNode,pObj);
	}
	else if ( OvRTTI_Util::IsTypeOf< OvStoreNode >( pObj ) )
	{
		return InsertStoreNode(rXmlNode,pObj);
	}
	return false;
}
bool OXU::SaveStoreToXml(OvStoreObject* pObj)
{
	if (pObj)
	{
		TiXmlDocument	kDoc;
		TiXmlElement	kRootElement(pObj->GetName());
		ConvertStoreObjectToElement(pObj,&kRootElement);
		kDoc.InsertEndChild(kRootElement);
		kDoc.SaveFile("../../export/storexml.xml");
		return true;
	}
	return false;
}
OvStoreObject* OXU::LoadXmlToStore()
{
	TiXmlDocument	kDoc;
	kDoc.LoadFile("../../export/storexml.xml");

	return false;
}