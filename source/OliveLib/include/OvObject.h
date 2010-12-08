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

	//!< AddExtraProperty�� ���� �߰��Ǵ� �߰� �Ӽ����� ������(exclusive)�̴�.
	//!< ���۷����� �Ѱ�����, ���ο��� OliveValue�� CopyFrom�� ���纻�� �����ϰ� �ȴ�.
	//!< �����͸� ����� ���� ��ü�� �ϳ��� �Ӽ��� �����Ҽ��� �ְ�����, ����μ��� �������ΰ�
	//!< �´°� ���� �̷��ϰ� �����ߴ�.
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