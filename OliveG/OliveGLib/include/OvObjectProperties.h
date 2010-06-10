#pragma once 

#include "OvMemObject.h"
#include "OvObjectID.h"
#include <queue>
#include <string>
using namespace std;

class OvObject;
class OvStorage;
struct SComponentLinkInfo : OvMemObject
{
	SComponentLinkInfo():formerID(OvObjectID::INVALID),linkDestination(){};
	OvObjectID	formerID;
	OvObject**	linkDestination;
};

class OvObjectProperties : public OvMemObject
{
public:
	static OvObjectProperties	INVALID;
public:

	void	SetObjectType(const string& );
	const string& GetObjectType();

	void	SetObjectID(const OvObjectID& rObjID);
	const OvObjectID& GetObjectID();

	void	PushValue(const string& rValue);
	bool	PopValue(string& rValue);

	void	PushComponentObject(OvObject* pObject);
	OvObject*	PopComponentObject();
	
	void	PushComponentLinkInfo(const SComponentLinkInfo& linkInfo);
	bool	PopComponentLinkInfo( SComponentLinkInfo& linkInfo );

private:
	queue<string>				m_queValueQueue;
	queue<OvObject*>			m_queObjects;
	queue<SComponentLinkInfo>	m_linkInfoQueue;
	string				m_objectType;
	OvObjectID			m_idObjectID;
};