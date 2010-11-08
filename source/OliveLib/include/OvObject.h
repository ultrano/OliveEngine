#pragma once
#include "OvUtility.h"
#include "OvRefBase.h"
#include "OvAutoPtr.h"
#include "OvPropertyBag.h"
#include <string>
#include <map>

#include "OvObjectID.h"

class OvStorage;
class OvObjectProperties;
OvREF_POINTER(OvObject);
namespace OliveValue
{
	class Value;
};
class OvObject : public OvRefBase
{
	OvRTTI_DECL(OvObject);
	OvPROPERTY_BAG_DECL(OvObject);
private:

	OvObject( OvObject& );
	OvObject( const OvObject& );

public:

	typedef std::map< std::string, OliveValue::Value* > extra_property_table;
	typedef std::pair< std::string, OliveValue::Value* > extra_property_table_pair;

	OvObject();
	virtual ~OvObject(); 

	//! Clone Object
	OvObjectSPtr Clone();

	//! Object Name
	void			SetName(const char* _pName);
	const string&	GetName();

	//! ID of Object
	OvObjectID		GetObjectID();

	//! Extra Property
	template<typename Type_0>
	Type_0* FindExtraProperty( const string& propName );
	OliveValue::Value* FindExtraProperty( const string& propName );

	//! RegisterExtraProperty는 성능상의 부하를 고려 해야 겠다. (구현부가 부하를 발생시키게 생겼다.)
	bool		RegisterExtraProperty( const string& propName, OliveValue::Value& extraProp );
	bool		RemoveExtraProperty( const string& propName );
	void		ClearExtraProperty();


private:

	OvObjectID		m_idObjectID;
	std::string		m_name;

	extra_property_table	m_extraPropertyTable;

};

template<typename Type_0>
Type_0* OvObject::FindExtraProperty( const string& propName )
{
	OliveValue::Value* extraValue = NULL;
	extraValue = FindExtraProperty( propName );
	if ( OvRTTI_Util::IsTypeOf<Type_0>( extraValue ) )
	{
		return ( Type_0* ) extraValue;
	}
	return NULL;
}
void ExtractProperties( OvObject* obj, OvObjectProperties& prop );
void InjectProperties( OvObject* obj, OvObjectProperties& prop );