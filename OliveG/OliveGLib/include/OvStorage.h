#pragma once
#include "OvMemObject.h"
#include "OvAutoPtr.h"
#include "OvSmartPointer.h"
#include "tinyxml.h"
#include "OvObject.h"

class OvObjectStore;

class OvStorage : public OvMemObject
{
public:

	OvStorage();
	~OvStorage();

	void	Store(const char* pFile);
	void	Restore(const char* pFile);

//private:

	void	StoreObject	 (OvObjectSPtr pObj);
	void	RestoreObject(OvObjectStore& rStore);

	bool	ExtractProperty	(OvObjectSPtr pObj,OvObjectStore& rStore);
	bool	InjectProperty	(OvObjectSPtr pObj,OvObjectStore& rStore);

	void	WriteProperty(OvObjectStore& rStore);
	//void	ReadStore(OvObjectSPtr _pObj);

	//OvObjectSPtr RestoreRelationshipTable();

private:

	struct OvPimple;
	OvAutoPtr< OvPimple> m_pPimple;

};
