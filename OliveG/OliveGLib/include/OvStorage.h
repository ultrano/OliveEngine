#pragma once
#include "OvMemObject.h"
#include "OvAutoPtr.h"
#include "OvSmartPointer.h"
#include "tinyxml.h"

OvREF_POINTER(OvObject);

class OvStorage : public OvMemObject
{
public:

	OvStorage();
	~OvStorage();

	void	Store(const char* pFile);
	void	Restore(const char* pFile);

	void	RegisterObject(OvObjectSPtr _pObj);
	void	RemoveObject(OvObjectSPtr _pObj);

	//OvObjectSPtr RestoreRelationshipTable();

private:

	struct OvPimple;
	OvAutoPtr< OvPimple> m_pPimple;

};
