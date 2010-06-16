#pragma once
#include "OvUtility.h"
#include "OvRefBase.h"
#include "OvAutoPtr.h"
#include "OvPropertyBag.h"
#include "OvExtraProperty.h"
#include <string>
#include <map>

#include "OvObjectID.h"

class OvStorage;
OvREF_POINTER(OvObject);
class OvObject : public OvRefBase
{
	OvRTTI_DECL(OvObject);
	OvPROPERTY_BAG_DECL(OvObject);

public:

	OvObject();
	OvObject(OvStorage& rStorage);
	~OvObject(); 

	//! Object Name
	void		SetName(const char* _pName);
	const char* GetName();

	//! ID of Object
	OvObjectID		GetObjectID();

	void		RegisterExtraProperty( const string& propName, OvExtraProperty::Value* extraProp );
	bool		RemoveExtraProperty( const string& propName );
	void		ClearExtraProperty();

	OvExtraProperty::Value* FindExtraProperty( const string& propName );

private:

	string			m_strObjectName;
	OvObjectID		m_idObjectID;

	typedef std::map< std::string, OvExtraProperty::Value* > extra_property_table;
	typedef std::pair< std::string, OvExtraProperty::Value* > extra_property_table_pair;
	extra_property_table	m_extraPropertyTable;

};

#define OvFACTORY_MEMBER(__class_name) friend class OvObjectFactory;\
__class_name(OvObjectID& objID){objID = GetObjectID();};\
static OvObjectSPtr	FactoryCallback(OvObjectID& objID){return (new __class_name(objID));};