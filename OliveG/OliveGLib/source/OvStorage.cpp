#include "OvStorage.h"
#include "OvStringUtility.h"
#include "OvObjectProperties.h"
#include "OvRTTI.h"
#include "OvPropertyBag.h"
#include "OvPropertyNode.h"
#include "OvProperty.h"
#include "OvObjectFactory.h"
#include "tinyxml.h"



OvStorage::OvStorage()
{

}
OvStorage::~OvStorage()
{

}
void	OvStorage::Store(const char* pFile)
{
}
void	OvStorage::Restore(const char* pFile)
{
}
void	OvStorage::StoreObject(OvObjectSPtr pObj)
{
	OvObjectProperties rStore;
	if (m_ocStoredObjects.IsCollected(pObj) == false && ExtractProperty(pObj,rStore))
	{
		WriteProperty(rStore);
		m_ocStoredObjects.AddObject(pObj);

		for (OvObject* kpSubObj = rStore.PopComponentObject()
			;kpSubObj != NULL
			;kpSubObj = rStore.PopComponentObject())
		{
			StoreObject(kpSubObj);
		}
	}
}
void	OvStorage::RestoreObject(OvObjectProperties& rStore)
{
	OvObjectID	createdObjID;
	OvObjectSPtr kpCreatedObj = OvObjectFactory::GetInstance()->CreateInstance(rStore.GetObjectType(),createdObjID);
	if (InjectProperty(kpCreatedObj,rStore))
	{
		m_mapCreatedObjects[rStore.GetObjectID()] = kpCreatedObj;
	}
}
bool	OvStorage::ExtractProperty(OvObjectSPtr pObj,OvObjectProperties& rStore)
{
	if (pObj)
	{
		OvRTTI* kpRTTI = NULL;
		for (kpRTTI = const_cast<OvRTTI*>(pObj->QueryRTTI())
			;kpRTTI && kpRTTI->PropertyBag()
			;kpRTTI = const_cast<OvRTTI*>(kpRTTI->GetBaseRTTI()))
		{
			OvPropertyBag* kpPropBag = kpRTTI->PropertyBag();
			if (kpPropBag)
			{
				OvPropertyNode* kpPropNode = NULL;
				for (kpPropNode = kpPropBag->BeginProperty()
					;kpPropNode != NULL
					;kpPropNode = kpPropNode->GetNext())
				{
					OvProperty* kpProp = kpPropNode->GetProperty();
					if (kpProp)
					{
						kpProp->Extract(pObj.GetRear(),rStore);
					}
				}
			}		
		}
		rStore.SetObjectType(OvRTTI_TypeName(pObj));
		rStore.SetObjectID(pObj->GetObjectID());
		return true;
	}
	return false;
}
bool	OvStorage::InjectProperty(OvObjectSPtr pObj,OvObjectProperties& rStore)
{
	if (pObj)
	{

		OvRTTI* kpRTTI = NULL;
		for (kpRTTI = const_cast<OvRTTI*>(pObj->QueryRTTI())
			;kpRTTI && kpRTTI->PropertyBag()
			;kpRTTI = const_cast<OvRTTI*>(kpRTTI->GetBaseRTTI()))
		{
			OvPropertyBag* kpPropBag = kpRTTI->PropertyBag();
			if (kpPropBag)
			{
				OvPropertyNode* kpPropNode = NULL;
				for (kpPropNode = kpPropBag->BeginProperty()
					;kpPropNode != NULL
					;kpPropNode = kpPropNode->GetNext())
				{
					OvProperty* kpProp = kpPropNode->GetProperty();
					if (kpProp)
					{
						kpProp->Inject(pObj.GetRear(),rStore);
					}
				}
			}
		}		
		return true;
	}
	return false;
}
void	OvStorage::WriteProperty(OvObjectProperties& rStore)
{
	TiXmlElement kObjNode(rStore.GetObjectType().data());
	kObjNode.SetAttribute("id",OvFormatString("%d",rStore.GetObjectID()));
	string kstrValue;
	while (rStore.PopValue(kstrValue))
	{
		TiXmlElement kPropSection("prop");
		kPropSection.InsertEndChild(TiXmlText(kstrValue.data()));
		kObjNode.InsertEndChild(kPropSection);
	}
	m_xmlDoc.InsertEndChild(kObjNode);
	m_xmlDoc.SaveFile("../../export/testprop.xml");
}