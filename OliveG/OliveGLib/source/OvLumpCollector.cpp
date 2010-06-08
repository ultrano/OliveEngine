#include "OvLumpCollector.h"


OvObjectPropertiesLump::OvObjectPropertiesLump(OvLumpCollector* _pCollector)
:m_pCollector(_pCollector)
,m_tixmlStoreData("Data")
{
	m_tixmlStoreData.Clear();
}
OvObjectPropertiesLump::~OvObjectPropertiesLump()
{

}

void	OvObjectPropertiesLump::SetObjectID(OvObjectID _cData)
{
	m_tixmlStoreData.SetAttribute("ObjectID",(int)_cData);
}
void	OvObjectPropertiesLump::SetObjectName(const char* _cData)
{
	m_tixmlStoreData.SetAttribute("ObjectName",_cData);
}
void	OvObjectPropertiesLump::SetObjectType(const char* _cData)
{
	m_tixmlStoreData.SetAttribute("ObjectType",_cData);
}

void	OvObjectPropertiesLump::StoreInt(const char* _pKey,int _cData)
{

}
void	OvObjectPropertiesLump::StoreFloat(const char* _pKey,float _cData)
{

}
void	OvObjectPropertiesLump::StoreString(const char* _pKey,const char* _cData)
{

}
void	OvObjectPropertiesLump::StoreRelationship(const char* _pKey,OvObjectSPtr _cData)
{
// 	if (_cData)
// 	{
// 		StoreInt(_pKey,(int)_cData->GetObjectID());
// 		m_pCollector->CollectObject(_cData);
// 	}
}

////////////////////////////////////////////////////////////////////////////////////////////
////////////////////////////////////////////////////////////////////////////////////////////
////////////////////////////////////////////////////////////////////////////////////////////
bool	OvLumpCollector::IsAlreadyCollected(OvObjectSPtr _pObj)
{
	return true;
}
void	OvLumpCollector::CollectObject(OvObjectSPtr _pObj)
{
	if (IsAlreadyCollected(_pObj) == false)
	{
		//_pObj->StoreProperty()
	}
}