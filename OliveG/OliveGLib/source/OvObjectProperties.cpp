#include "OvObjectProperties.h"
#include "OliveValue.h"

OvObjectProperties	OvObjectProperties::INVALID;

void	OvObjectProperties::SetObjectType(const string& objType)
{
	m_objectType = objType;
}

const string& OvObjectProperties::GetObjectType()
{
	return m_objectType;
}

void	OvObjectProperties::SetObjectID(const OvObjectID& rObjID)
{
	m_idObjectID = rObjID;
}

const OvObjectID& OvObjectProperties::GetObjectID()
{
	return m_idObjectID;
}

void	OvObjectProperties::PushValue(const string& rValue)
{
	m_queValueQueue.push(rValue);
}

bool	OvObjectProperties::PopValue(string& rValue)
{
	if (m_queValueQueue.size())
	{
		rValue = m_queValueQueue.front();
		m_queValueQueue.pop();
		return true;
	}
	return false;
}
void	OvObjectProperties::PushValue( OliveValue::Value& rValue )
{
	PushValue(rValue.GetValue());
}
bool	OvObjectProperties::PopValue( OliveValue::Value& rValue )
{
	string popedValue;
	if(PopValue(popedValue))
	{
		rValue.SetValue(popedValue);
		return true;
	}
	return false;
}

void	OvObjectProperties::PushComponentObject(OvObject* pObject)
{
	m_queObjects.push(pObject);
}
OvObject*	OvObjectProperties::PopComponentObject()
{
	if (m_queObjects.size())
	{
		OvObject* kpObj = m_queObjects.front();
		m_queObjects.pop();
		return kpObj;
	}
	return NULL;
}

void OvObjectProperties::PushComponentLinkInfo( const SComponentLinkInfo& linkInfo )
{
	m_linkInfoQueue.push(linkInfo);
}

bool OvObjectProperties::PopComponentLinkInfo( SComponentLinkInfo& linkInfo )
{
	if (m_linkInfoQueue.size())
	{
		linkInfo = m_linkInfoQueue.front();
		m_linkInfoQueue.pop();
		return true;
	}
	return false;
}