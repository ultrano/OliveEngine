#include "OvStreamer.h"
#include "OvObjectCollector.h"
#include "OvStringUtility.h"
#include "OvObjectData.h"
#include "OvRTTI.h"
#include "OvPropertyBag.h"
#include "OvPropertyNode.h"
#include "OvProperty.h"
#include "OvObjectFactory.h"
#include "tinyxml.h"
using namespace std;
struct OvStreamer::OvPimple : OvMemObject
{
	TiXmlDocument					m_xmlDoc;
	OvObjectCollector				m_ocStoredObjects;
	map<OvObjectID,OvObjectSPtr>	m_mapCreatedObjects;
};


OvStreamer::OvStreamer()
:m_pPimple(OvNew OvStreamer::OvPimple)
{

}
OvStreamer::~OvStreamer()
{

}
void	OvStreamer::Store(const char* pFile)
{
}
void	OvStreamer::Restore(const char* pFile)
{
}
void	OvStreamer::StoreObject(OvObjectSPtr pObj)
{
	OvObjectData rStore;
	if (ExtractProperty(pObj,rStore))
	{
		WriteProperty(rStore);
		m_pPimple->m_ocStoredObjects.AddObject(pObj);

		for (OvObject* kpSubObj = rStore.PopAddedObject()
			;kpSubObj != NULL
			;kpSubObj = rStore.PopAddedObject())
		{
			StoreObject(kpSubObj);
		}
	}
}
void	OvStreamer::RestoreObject(OvObjectData& rStore)
{
	OvObjectSPtr kpCreatedObj = OvObjectFactory::GetInstance()->CreateInstance(rStore.GetClass(),*this);
	if (InjectProperty(kpCreatedObj,rStore))
	{
		m_pPimple->m_mapCreatedObjects[rStore.GetObjectID()] = kpCreatedObj;
	}
}
bool	OvStreamer::ExtractProperty(OvObjectSPtr pObj,OvObjectData& rStore)
{
	if (pObj && m_pPimple->m_ocStoredObjects.IsCollected(pObj) == false)
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
		rStore.SetClass(OvRTTI_TypeName(pObj));
		rStore.SetObjectID(pObj->GetObjectID());
		return true;
	}
	return false;
}
bool	OvStreamer::InjectProperty(OvObjectSPtr pObj,OvObjectData& rStore)
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
void	OvStreamer::WriteProperty(OvObjectData& rStore)
{
	TiXmlElement kObjNode(rStore.GetClass().data());
	kObjNode.SetAttribute("id",OvFormatString("%d",rStore.GetObjectID()));
	string kstrValue;
	while (rStore.PopValue(kstrValue))
	{
		TiXmlElement kPropSection("prop");
		kPropSection.InsertEndChild(TiXmlText(kstrValue.data()));
		kObjNode.InsertEndChild(kPropSection);
	}
	m_pPimple->m_xmlDoc.InsertEndChild(kObjNode);
	m_pPimple->m_xmlDoc.SaveFile("../../export/testprop.xml");
}