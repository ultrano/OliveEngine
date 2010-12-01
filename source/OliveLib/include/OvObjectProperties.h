#pragma once 

#include "OvMemObject.h"
#include "OvObjectID.h"
#include "OvStreamCommon.h"
#include <queue>
#include <list>
using namespace std;

class OvObject;
class OvStorage;
namespace OliveValue
{
	class Value;
};

// traverser? ¿Ã∏ß¿ª πŸ≤„¡‡æﬂ «œ≥™?
class OvObjectProperties : public OvMemObject
{
public:

	OvObjectProperties();
	~OvObjectProperties();

	void	SetObjectType(const string& );
	const string& GetObjectType();

	void	SetObjectID(const OvObjectID& rObjID);
	const OvObjectID& GetObjectID();

	void	PushValue(const string& rValue);
	bool	PopValue(string& rValue);

	void	PushValue( OliveValue::Value& rValue );
	bool	PopValue( OliveValue::Value& rValue );

	void	PushAssociatedObject(OvObject* pObject);
	OvObject*	PopComponentObject();

	void	CollectLinkBuilder( OvAssociatedLinkConnector* linkBuilder);
	void	LinkBuilderListMoveTo( link_builder_list& builderList );

private:
	queue<string>		m_queValueQueue;
	queue<OvObject*>	m_queObjects;
	string				m_objectType;
	OvObjectID			m_idObjectID;
	link_builder_list	m_collectedLinkBuilder;
};