#pragma once
#include "OvSingleton.h"
#include "OvUtility.h"
#include "OvObjectID.h"
#include <map>


class OvObjectManager : public OvSingleton< OvObjectManager >
{
	OvSINGLETON(OvObjectManager);
	friend class OvObject;
	typedef std::map<OvObjectID,OvObject*>			object_table;

public:

	OvObjectManager();
	~OvObjectManager();

	OvObject*			FindObject(const OvObjectID& rObjHandle);

protected:

	OvObjectID			AllocObjectID(OvObject* _pObject);
	void				RecallObjectID(OvObject* _pObject);

private:
	OvObjectID		m_maxID;
	object_table	m_objectTable;
};