#pragma once 

#include "OvMemObject.h"
#include <queue>
#include <string>
using namespace std;
class OvObject;

class OvStorage;

#include "OvObjectID.h"

class OvObjectStore : public OvMemObject
{
public:
	static OvObjectStore	INVALID;
public:

	void	SetClass(const string& );
	const string& GetClass();

	void	SetObjectID(const OvObjectID& rObjID);
	const OvObjectID& GetObjectID();

	void	PushValue(const string& rValue);
	bool	PopValue(string& rValue);

	void	PushObject(OvObject* pObject);
	OvObject*	PopAddedObject();
	
private:
	queue<string>		m_queValueQueue;
	queue<OvObject*>	m_queObjects;
	string				m_strClass;
	OvObjectID			m_idObjectID;
};