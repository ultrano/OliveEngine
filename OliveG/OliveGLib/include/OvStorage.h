#pragma once
#include "OvMemObject.h"
#include "OvAutoPtr.h"
#include "OvSmartPointer.h"
#include "tinyxml.h"
#include "OvObject.h"
#include "OvObjectCollector.h"
#include <map>

class OvObjectProperties;

class OvStorage : public OvMemObject
{
public:

	OvStorage();
	~OvStorage();

	void	Store(const char* pFile);
	void	Restore(const char* pFile);

//private:

	void	StoreObject	 (OvObjectSPtr pObj);
	void	RestoreObject(OvObjectProperties& rStore);

	bool	ExtractProperty	(OvObjectSPtr pObj,OvObjectProperties& rStore);
	bool	InjectProperty	(OvObjectSPtr pObj,OvObjectProperties& rStore);

	void	WriteProperty(OvObjectProperties& rStore);
	void	ReadProperty(const string& fileName);
	//void	ReadStore(OvObjectSPtr _pObj);

	//OvObjectSPtr RestoreRelationshipTable();

private:

	TiXmlDocument					m_xmlDoc;
	OvObjectCollector				m_ocStoredObjects;
	std::map<OvObjectID,OvObjectSPtr>	m_mapCreatedObjects;

};
