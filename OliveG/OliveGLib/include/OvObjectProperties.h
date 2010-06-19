#pragma once 

#include "OvMemObject.h"
#include "OvObjectID.h"
#include <queue>
#include <string>
using namespace std;

class OvObject;
class OvStorage;
class OvRelationLinkBuilder;
namespace OliveValue
{
	class Value;
};

class OvObjectProperties : public OvMemObject
{
public:
	static OvObjectProperties	INVALID;
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

	void	PushComponentObject(OvObject* pObject);
	OvObject*	PopComponentObject();

	void	CollectLinkBuilder( OvRelationLinkBuilder* linkBuilder);
	OvRelationLinkBuilder* HandoverHeadLinkBuilder();

private:
	queue<string>		m_queValueQueue;
	queue<OvObject*>	m_queObjects;
	string				m_objectType;
	OvObjectID			m_idObjectID;
	OvRelationLinkBuilder*		m_headLinkBuilder;
};