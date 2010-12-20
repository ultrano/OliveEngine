#pragma once 

#include "OvMemObject.h"
#include "OvObjectID.h"
#include "OvStreamCommon.h"
#include <queue>
#include <list>
using namespace std;

class OvObject;
class OvStorage;
namespace OliveValue{class Value;};

// traverser? ¿Ã∏ß¿ª πŸ≤„¡‡æﬂ «œ≥™?
class OvObjectProperties : public OvMemObject
{
public:

	OvObjectProperties();
	~OvObjectProperties();

	void	SetObjectType(const OvString& );
	const OvString& GetObjectType();

	void	SetObjectID(const OvObjectID& rObjID);
	const OvObjectID& GetObjectID();

	void	PushValue(const OvString& rValue);
	OvBool	PopValue(OvString& rValue);

	void	PushValue( OliveValue::Value& rValue );
	OvBool	PopValue( OliveValue::Value& rValue );

	void	PushAssociatedObject(OvObject* pObject);

	void	PushAssociatedLinkConnector( OvAssociatedLinkConnector* linkBuilder);

private:
	queue<OvString>		m_queValueQueue;
	queue<OvObject*>	m_queObjects;
	OvString				m_objectType;
	OvObjectID			m_idObjectID;
	link_builder_list	m_collectedLinkBuilder;
};