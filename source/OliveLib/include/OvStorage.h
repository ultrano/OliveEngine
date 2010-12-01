#pragma once
#include "OvMemObject.h"
#include "OvAutoPtr.h"
#include "OvSmartPointer.h"
#include "tinyxml.h"
#include "OvObjectCollector.h"
#include "OvStreamCommon.h"

class OvObjectProperties;
class OvAssociatedLinkConnector;
class OvObject;

class OvStorage : public OvMemObject
{
public:
	

	OvStorage();
	~OvStorage();

	OvBool	Save( const OvString& pFile, OvObjectCollector& saveObjects);
	OvBool	Load( const OvString& pFile, OvObjectCollector& loadedObjects);

	void	Clear();

private:

	void	_store_object	 (OvObject* pObj);
	void	_restore_object( TiXmlElement& objElem );

	OvBool	_extract_property	(OvObject* pObj,OvObjectProperties& rStore);
	OvBool	_inject_property	(OvObject* pObj,OvObjectProperties& rStore);

	OvBool	_write_property(OvObjectProperties& rStore, TiXmlElement& objElem);
	OvBool	_read_property( TiXmlElement& objElem, OvObjectProperties& rStore );

	void	_rebuild_related_link( restore_object_table& restoreTable, link_builder_list& linkBuilderList );

private:

	TiXmlDocument			m_xmlDoc;
	OvObjectCollector		m_storeObjectTable;

	restore_object_table	m_restoreObjectTable;
	link_builder_list		m_linkBuilderList;

};
