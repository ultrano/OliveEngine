#pragma once
#include "OvUtility.h"
#include "OvRefBase.h"
#include "OvAutoPtr.h"
#include "OvPropertyBag.h"
#include "OvObjectFactory.h"
#include <map>

#include "OvObjectID.h"

class OvStorage;
class OvObjectProperties;
OvREF_POINTER(OvObject);
namespace OliveValue
{
	OvREF_POINTER(Value);
};
class OvObject : public OvRefBase
{
	OvRTTI_DECL(OvObject);
	OvPROPERTY_BAG_DECL(OvObject);
private:

	OvObject( OvObject& );
	OvObject( const OvObject& );

public:

	typedef std::map< OvString, OliveValue::ValueSPtr > extra_property_table;
	typedef std::pair< OvString, OliveValue::ValueSPtr > extra_property_table_pair;

	OvObject();
	virtual ~OvObject(); 

	//! Clone Object
	OvObjectSPtr Clone();

	//! Object Name
	void			SetName(const OvChar* _pName);
	const OvString&	GetName();

	//! ID of Object
	OvObjectID		GetObjectID();

	//! Extra Property
	template<typename Type_0>
	OvSmartPointer<Type_0> FindExtraProperty( const OvString& propName );
	OliveValue::ValueSPtr FindExtraProperty( const OvString& propName );

	//!< AddExtraProperty에 의해 추가되는 추가 속성들은 독점적(exclusive)이다.
	//!< 레퍼런스로 넘겨지며, 내부에서 OliveValue의 CopyFrom을 복사본을 소지하게 된다.
	//!< 포인터를 사용해 여러 객체가 하나의 속성을 공유할수도 있겠지만, 현재로서는 독점적인게
	//!< 맞는거 같아 이러하게 구현했다.
	OvBool		AddExtraProperty( const OvString& propName, OliveValue::Value& extraProp );
	OvBool		RemoveExtraProperty( const OvString& propName );
	void		ClearExtraProperties();


private:

	OvObjectID		m_idObjectID;
	OvString		m_name;

	extra_property_table	m_extraPropertyTable;

};

template<typename Type_0>
OvSmartPointer<Type_0> OvObject::FindExtraProperty( const OvString& propName )
{
	OliveValue::ValueSPtr extraValue = NULL;
	extraValue = FindExtraProperty( propName );
	if ( OvRTTI_Util::IsTypeOf<Type_0>( extraValue ) )
	{
		return extraValue;
	}
	return NULL;
}
void ExtractProperties( OvObject* obj, OvObjectProperties& prop );
void InjectProperties( OvObject* obj, OvObjectProperties& prop );