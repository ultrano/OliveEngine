#include "OvStorage.h"
#include "OvStringUtility.h"
#include "OvObjectProperties.h"
#include "OvUtility_RTTI.h"
#include "OvPropertyBag.h"
#include "OvPropertyAccesser.h"
#include "OvObject.h"
#include "OvObjectFactory.h"
#include "OvAssociatedLinkConnector.h"
#include "OvObjectID.h"
#include "tinyxml.h"

OvStorage::OvStorage()
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
bool	OvStorage::Save( const OvString& pFile, OvObjectCollector& saveObjects )
{
	SAutoStoreCleaner autoCleaner(this);

	TiXmlElement rootElement("ObjectTable");
	m_xmlDoc.InsertEndChild(rootElement);

	for ( unsigned i = 0 ; i < saveObjects.Count() ; ++i)
	{
		OvObjectSPtr streObj = saveObjects.GetByAt(i);
		_store_object( streObj.GetRear() );
	}

	return m_xmlDoc.SaveFile( pFile.c_str() );
}

bool	OvStorage::Load( const OvString& pFile, OvObjectCollector& loadedObjects)
{
	SAutoStoreCleaner autoCleaner(this);

	if ( m_xmlDoc.LoadFile( pFile.c_str(), TIXML_ENCODING_UTF8 ) )
	{
		TiXmlElement* rootElem = m_xmlDoc.RootElement();

		for ( TiXmlElement* objElem = rootElem->FirstChildElement("Object")
			; objElem != NULL
			; objElem = objElem->NextSiblingElement("Object") )
		{
			_restore_object( *objElem );
		}
		_rebuild_related_link( m_restoreObjectTable, m_linkBuilderList );

		for each( restore_object_table::value_type tableIter in m_restoreObjectTable )
		{
			loadedObjects.AddObject( tableIter.second );
		}
		return true;
	}
	return false;
}

void	OvStorage::_store_object(OvObject* pObj)
{
	OvObjectProperties rStore;
	if ( _extract_property(pObj,rStore) )
	{
		TiXmlElement objElem("");
		if ( _write_property( rStore, objElem ) )
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
				_store_object(kpSubObj);
			}
		}
	}
}
void	OvStorage::_restore_object( TiXmlElement& objElem )
{
	OvObjectProperties rStore;
	if ( _read_property( objElem, rStore ) )
	{
		OvObject* restoreObj = Olive::CreateObject_Ptr( rStore.GetObjectType() );
		if ( _inject_property( restoreObj, rStore ) )
		{
			m_restoreObjectTable[ rStore.GetObjectID() ] = restoreObj;
			rStore.LinkBuilderListMoveTo( m_linkBuilderList );
		}
	}
}
bool	OvStorage::_extract_property(OvObject* pObj,OvObjectProperties& rStore)
{
	if (pObj && m_storeObjectTable.IsCollected(pObj) == false )
	{

		ExtractProperties( pObj, rStore );
		OvString typeName = OvRTTI_Util::TypeName( pObj );
		rStore.SetObjectType( typeName );
		rStore.SetObjectID(pObj->GetObjectID());

		m_storeObjectTable.AddObject(pObj);

		return true;
	}
	return false;
}
bool	OvStorage::_inject_property(OvObject* pObj,OvObjectProperties& rStore)
{
	if (pObj)
	{
		InjectProperties( pObj, rStore );
		return true;
	}
	return false;
}
bool	OvStorage::_write_property(OvObjectProperties& rStore, TiXmlElement& objElem)
{
	objElem.SetValue("Object");
	objElem.SetAttribute("type", rStore.GetObjectType().c_str() );
	objElem.SetAttribute("id",OvFormatString("%d",rStore.GetObjectID()));

	OvString kstrValue;
	while (rStore.PopValue(kstrValue))
	{
		TiXmlElement kPropSection("prop");
		kPropSection.InsertEndChild(TiXmlText(kstrValue.data()));
		objElem.InsertEndChild(kPropSection);
	}
	return true;
}

bool	OvStorage::_read_property( TiXmlElement& objElem, OvObjectProperties& rStore )
{
	if ( OvString("Object") == objElem.Value() )
	{

		OvObjectID	formerId;
		objElem.Attribute( "id", (OvInt*)&formerId );
		OvString	typeName = objElem.Attribute( "type" );

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
void	OvStorage::_rebuild_related_link( restore_object_table& restoreTable, link_builder_list& linkBuilderList )
{
	if ( restoreTable.size() && linkBuilderList.size() )
	{
		for each( OvAssociatedLinkConnector* linkBuilder in linkBuilderList )
		{
			if (linkBuilder)
			{
				linkBuilder->BuildLink(restoreTable);
			}
		}
	}
}
void	OvStorage::Clear()
{
	m_xmlDoc.Clear();;
	m_storeObjectTable.Clear();

	m_restoreObjectTable.clear();

	if ( m_linkBuilderList.size() )
	{
		for each( OvAssociatedLinkConnector* linkBuilder in m_linkBuilderList )
		{
			if (linkBuilder)
			{
				delete linkBuilder;
			}
		}
		m_linkBuilderList.clear();
	}
}