#pragma once
#include "OvMemObject.h"
#include "OvAutoPtr.h"
#include "OvSmartPointer.h"
#include "tinyxml.h"
#include "OvObjectCollector.h"
#include "OvStreamCommon.h"

class OvObjectProperties;
class OvRelationLinkBuilder;
class OvObject;

class OvStorage : public OvMemObject
{
public:
	

	OvStorage();
	~OvStorage();

	void	Save(const char* pFile, OvObjectCollector& saveObjects);
	void	Load(const char* pFile, OvObjectCollector& loadedObjects);

	void	StoreObject	 (OvObject* pObj);
	void	RestoreObject( TiXmlElement& objElem );

	bool	ExtractProperty	(OvObject* pObj,OvObjectProperties& rStore);
	bool	InjectProperty	(OvObject* pObj,OvObjectProperties& rStore);

	bool	WriteProperty(OvObjectProperties& rStore, TiXmlElement& objElem);
	bool	ReadProperty( TiXmlElement& objElem, OvObjectProperties& rStore );

	void	RebuildRelatedLink( restore_object_table& restoreTable, link_builder_list& linkBuilderList );

	void	Clear();

private:

	TiXmlDocument			m_xmlDoc;
	OvObjectCollector		m_storeObjectTable;

	restore_object_table	m_restoreObjectTable;
	link_builder_list		m_linkBuilderList;

};
