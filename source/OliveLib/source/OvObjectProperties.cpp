#include "OvObjectProperties.h"
#include "OliveValue.h"
#include "OvAssociatedLinkConnector.h"


OvObjectProperties::OvObjectProperties()
:m_idObjectID( OvObjectID::INVALID )
{

}
OvObjectProperties::~OvObjectProperties()
{
	while (m_queValueQueue.size())
	{
		m_queValueQueue.pop();
	}

	for each( OvAssociatedLinkConnector* linkBuilder in m_collectedLinkBuilder )
	{
		if (linkBuilder)
		{
			delete linkBuilder;
		}
	}
	m_collectedLinkBuilder.clear();

}

void	OvObjectProperties::SetObjectType(const OvString& objType)
{
	m_objectType = objType;
}

const OvString& OvObjectProperties::GetObjectType()
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

void	OvObjectProperties::PushValue(const OvString& rValue)
{
	m_queValueQueue.push(rValue);
}

OvBool	OvObjectProperties::PopValue(OvString& rValue)
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
	PushValue(rValue.ToString());
}
OvBool	OvObjectProperties::PopValue( OliveValue::Value& rValue )
{
	OvString popedValue;
	if(PopValue(popedValue))
	{
		rValue.FromString(popedValue);
		return true;
	}
	return false;
}

void	OvObjectProperties::PushAssociatedObject(OvObject* pObject)
{
	if (pObject)
	{
		m_queObjects.push(pObject);
	}
}
void		OvObjectProperties::PushAssociatedLinkConnector( OvAssociatedLinkConnector* linkBuilder)
{
	m_collectedLinkBuilder.push_back( linkBuilder );
}