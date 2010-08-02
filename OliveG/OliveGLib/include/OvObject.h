#pragma once
#include "OvUtility.h"
#include "OvRefBase.h"
#include "OvAutoPtr.h"
#include "OvPropertyBag.h"
#include <string>
#include <map>

#include "OvObjectID.h"

class OvStorage;
OvREF_POINTER(OvObject);
namespace OliveValue
{
	class Value;
};
class OvObject : public OvRefBase
{
	OvRTTI_DECL(OvObject);
	OvPROPERTY_BAG_DECL(OvObject);

public:

	typedef std::map< std::string, OliveValue::Value* > extra_property_table;
	typedef std::pair< std::string, OliveValue::Value* > extra_property_table_pair;

	OvObject();
	OvObject(OvStorage& rStorage);
	virtual ~OvObject(); 

	//! Object Name
	void		SetName(const char* _pName);
	const string& GetName();

	//! ID of Object
	OvObjectID		GetObjectID();

	void		RegisterExtraProperty( const string& propName, OliveValue::Value* extraProp );
	bool		RemoveExtraProperty( const string& propName );
	void		ClearExtraProperty();

	OliveValue::Value* FindExtraProperty( const string& propName );

private:

	OvObjectID		m_idObjectID;

	extra_property_table	m_extraPropertyTable;

};

#define OvFACTORY_MEMBER(__class_name) friend class OvObjectFactory;\
__class_name(OvObjectID& objID){objID = GetObjectID();};\
static OvObjectSPtr	FactoryCallback(OvObjectID& objID){return (new __class_name(objID));};