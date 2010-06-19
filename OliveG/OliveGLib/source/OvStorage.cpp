#include "OvStorage.h"
#include "OvStringUtility.h"
#include "OvObjectProperties.h"
#include "OvUtility_RTTI.h"
#include "OvPropertyBag.h"
#include "OvPropertyNode.h"
#include "OvProperty.h"
#include "OvObject.h"
#include "OvRelationLinkBuilder.h"
#include "tinyxml.h"

////////////////////// 테스트 인클루드 (물리적 구조때문에 나중에 지워줘야 한다.) /////
#include "OvCamera.h"
#include "OvXNode.h"
OvObject* TemporaryFactoryFunction(const string& typeName);
//////////////////////////////////////////////////////////////////////////

OvStorage::OvStorage()
:m_headBuilder(NULL)
{

}
OvStorage::~OvStorage()
{
	Clear();
}
struct SAutoStoreCleaner
{
	OvStorage* m_cleanTarget;
	SAutoStoreCleaner(OvStorage* cleanTarget):m_cleanTarget(cleanTarget){};
	~SAutoStoreCleaner(){if(m_cleanTarget)m_cleanTarget->Clear();};
};
void	OvStorage::Save(const char* pFile, OvObjectCollector& saveObjects )
{
	SAutoStoreCleaner autoCleaner(this);

	TiXmlElement rootElement("ObjectTable");
	m_xmlDoc.InsertEndChild(rootElement);

	for (int i = 0 ; i < saveObjects.Count() ; ++i)
	{
		OvObjectSPtr streObj = saveObjects.GetByAt(i);
		StoreObject( streObj.GetRear() );
	}

	m_xmlDoc.SaveFile( pFile );
}

void	OvStorage::Load(const char* pFile, OvObjectCollector& loadedObjects)
{
	SAutoStoreCleaner autoCleaner(this);

	m_xmlDoc.LoadFile( pFile, TIXML_ENCODING_UTF8 );
	TiXmlElement* rootElem = m_xmlDoc.RootElement();
	TiXmlElement* firstObjElem = rootElem->FirstChildElement("Object");
	if ( firstObjElem )
	{
		RestoreObject( *firstObjElem );
	}
	RebuildRelatedLink( m_restoreObjectTable, m_headBuilder );

	for each( restore_object_table::value_type tableIter in m_restoreObjectTable )
	{
		loadedObjects.AddObject( tableIter.second );
	}
}
void	OvStorage::StoreObject(OvObject* pObj)
{
	OvObjectProperties rStore;
	if ( ExtractProperty(pObj,rStore) )
	{
		TiXmlElement objElem("");
		if ( WriteProperty( rStore, objElem ) )
		{
			TiXmlElement* rootElem = m_xmlDoc.RootElement();
			if (rootElem)
			{
				rootElem->InsertEndChild( objElem );
			}

			for (OvObject* kpSubObj = rStore.PopComponentObject()
				;kpSubObj != NULL
				;kpSubObj = rStore.PopComponentObject())
			{
				StoreObject(kpSubObj);
			}
		}
	}
}
void	OvStorage::RestoreObject( TiXmlElement& objElem )
{
	OvObjectProperties rStore;
	if ( ReadProperty( objElem, rStore ) )
	{
		OvObject* restoreObj = TemporaryFactoryFunction( rStore.GetObjectType() );
		if ( InjectProperty( restoreObj, rStore ) )
		{
			m_restoreObjectTable[ rStore.GetObjectID() ] = restoreObj;
			OvRelationLinkBuilder* headBuilder = rStore.HandoverHeadLinkBuilder();
			if ( headBuilder )
			{
				headBuilder->SetNextBuilder( m_headBuilder );
				m_headBuilder = headBuilder;
			}
		}
	}
	if (TiXmlElement* nextElem = objElem.NextSiblingElement("Object"))
	{
		RestoreObject( *nextElem );
	}
}
bool	OvStorage::ExtractProperty(OvObject* pObj,OvObjectProperties& rStore)
{
	if (pObj && m_storeObjectTable.IsCollected(pObj) == false )
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
						kpProp->Extract(pObj,rStore);
					}
				}
			}		
		}
		rStore.SetObjectType(OvRTTI_Util::TypeName(pObj));
		rStore.SetObjectID(pObj->GetObjectID());

		m_storeObjectTable.AddObject(pObj);

		return true;
	}
	return false;
}
bool	OvStorage::InjectProperty(OvObject* pObj,OvObjectProperties& rStore)
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
						kpProp->Inject(pObj,rStore);
					}
				}
			}
		}		
		return true;
	}
	return false;
}
bool	OvStorage::WriteProperty(OvObjectProperties& rStore, TiXmlElement& objElem)
{
	objElem.SetValue("Object");
	objElem.SetAttribute("type", rStore.GetObjectType().c_str() );
	objElem.SetAttribute("id",OvFormatString("%d",rStore.GetObjectID()));

	string kstrValue;
	while (rStore.PopValue(kstrValue))
	{
		TiXmlElement kPropSection("prop");
		kPropSection.InsertEndChild(TiXmlText(kstrValue.data()));
		objElem.InsertEndChild(kPropSection);
	}
	return true;
}

bool	OvStorage::ReadProperty( TiXmlElement& objElem, OvObjectProperties& rStore )
{
	if ( string("Object") == objElem.Value() )
	{

		OvObjectID	formerId;
		objElem.Attribute( "id", (int*)&formerId );
		string	typeName = objElem.Attribute( "type" );

		rStore.SetObjectType(typeName);
		rStore.SetObjectID(formerId);

		for ( TiXmlElement* propElem = objElem.FirstChildElement( "prop" )
			; propElem != NULL
			; propElem = propElem->NextSiblingElement( "prop" ) )
		{
			if (propElem->GetText())
			{
				rStore.PushValue( propElem->GetText() );
			}
			else
			{
				rStore.PushValue( "" );
			}
		}
		return true;
	}
	return false;
}
void	OvStorage::RebuildRelatedLink( OvStorage::restore_object_table& restoreTable, OvRelationLinkBuilder* headBuilder )
{
	if ( restoreTable.size() && headBuilder )
	{
		for ( OvRelationLinkBuilder* linkBuilder = headBuilder
			; linkBuilder != NULL
			; linkBuilder = linkBuilder->GetNextBuilder()
			)
		{
			linkBuilder->BuildLink(restoreTable);
		}
	}
}
void	OvStorage::Clear()
{
	m_xmlDoc.Clear();;
	m_storeObjectTable.Clear();

	m_restoreObjectTable.clear();

	if (m_headBuilder)
	{
		for ( OvRelationLinkBuilder* deleteTarget = m_headBuilder
			; deleteTarget != NULL
			; deleteTarget = deleteTarget->GetNextBuilder() )
		{
			delete deleteTarget;
		}
		m_headBuilder = NULL;
	}
}
OvObject* TemporaryFactoryFunction(const string& typeName)
{
	if ("OvXNode" == typeName)
	{
		return new OvXNode;
	}
	else if ("OvCamera" == typeName)
	{
		return new OvCamera;
	}
	return NULL;
}