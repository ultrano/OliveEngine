#pragma once
#include "OvMemObject.h"
#include "OvObject.h"
#include "tinyxml.h"

class OvLumpCollector;
class OvObjectDataLump : public OvMemObject
{

public:

	OvObjectDataLump(OvLumpCollector* _pCollector);
	~OvObjectDataLump();

private:

	void	SetObjectID(OvObjectID _cData);
	void	SetObjectName(const char* _cData);
	void	SetObjectType(const char* _cData);
	
public:

	void	StoreInt(const char* _pKey,int _cData);
	void	StoreFloat(const char* _pKey,float _cData);
	void	StoreString(const char* _pKey,const char* _cData);
	void	StoreRelationship(const char* _pKey,OvObjectSPtr _cData);

private:

	TiXmlElement	m_tixmlStoreData;
	const OvLumpCollector* m_pCollector;

};

class OvLumpCollector : public OvMemObject
{
public:

	bool	IsAlreadyCollected(OvObjectSPtr _pObj);
	void	CollectObject(OvObjectSPtr _pObj);

private:

	struct OvPimple;
	OvAutoPtr< OvPimple> m_pPimple;

};