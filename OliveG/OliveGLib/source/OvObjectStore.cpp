#include "OvObjectStore.h"

OvObjectStore	OvObjectStore::INVALID;

void	OvObjectStore::SetClass(const string& rClass)
{
	m_strClass = rClass;
}
const string& OvObjectStore::GetClass()
{
	return m_strClass;
}

void	OvObjectStore::SetObjectID(const OvObjectID& rObjID)
{
	m_idObjectID = rObjID;
}
const OvObjectID& OvObjectStore::GetObjectID()
{
	return m_idObjectID;
}

void	OvObjectStore::PushValue(const string& rValue)
{
	m_queValueQueue.push(rValue);
}

bool	OvObjectStore::PopValue(string& rValue)
{
	if (m_queValueQueue.size())
	{
		rValue = m_queValueQueue.front();
		m_queValueQueue.pop();
		return true;
	}
	return false;
}

void	OvObjectStore::PushObject(OvObject* pObject)
{
	m_queObjects.push(pObject);
}
OvObject*	OvObjectStore::PopAddedObject()
{
	if (m_queObjects.size())
	{
		OvObject* kpObj = m_queObjects.front();
		m_queObjects.pop();
		return kpObj;
	}
	return NULL;
}