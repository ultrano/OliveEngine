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

	bool	Save( const std::string& pFile, OvObjectCollector& saveObjects);
	bool	Load( const std::string& pFile, OvObjectCollector& loadedObjects);

	void	Clear();

private:

	void	_store_object	 (OvObject* pObj);
	void	_restore_object( TiXmlElement& objElem );

	bool	_extract_property	(OvObject* pObj,OvObjectProperties& rStore);
	bool	_inject_property	(OvObject* pObj,OvObjectProperties& rStore);

	bool	_write_property(OvObjectProperties& rStore, TiXmlElement& objElem);
	bool	_read_property( TiXmlElement& objElem, OvObjectProperties& rStore );

	void	_rebuild_related_link( restore_object_table& restoreTable, link_builder_list& linkBuilderList );

private:

	TiXmlDocument			m_xmlDoc;
	OvObjectCollector		m_storeObjectTable;

	restore_object_table	m_restoreObjectTable;
	link_builder_list		m_linkBuilderList;

};
OvObject* TemporaryFactoryFunction(const string& typeName);