#pragma once

#include "OvAutoPtr.h"
#include <vector>
#include <string>

class OvPropertyAccesser;

class OvPropertyBag
{
public:

	OvPropertyBag();
	~OvPropertyBag();

	unsigned			GetPropertiesCount();
	OvPropertyAccesser* GetPropertyAt( unsigned index );
	OvPropertyAccesser* FindProperty( const std::string& name );

	void				AddProperty(OvPropertyAccesser* pProperty);

private:

	vector< OvAutoPtr<OvPropertyAccesser> > m_properties;

};

#define OvPROPERTY_BAG_DECL(_classname) private:static OvPropertyBag msh_OvPropertyBag;\
	friend struct __SPropertiesDeclare_##_classname;\
	public:static OvPropertyBag* _getPropertyBag(){return &msh_OvPropertyBag;};\
//

#define	OvPROPERTY_BAG_BEGIN(_classname) OvPropertyBag _classname::msh_OvPropertyBag;\
struct __SPropertiesDeclare_##_classname \
{\
	typedef _classname target_class;\
	__SPropertiesDeclare_##_classname()\
	{\

//

#define OvPROPERTY_BAG_REGISTER(_prop_type,_property) {OvPropertyAccesser* kpProp = new _prop_type;\
	kpProp->SetOffset(offsetof(target_class,_property));\
	kpProp->SetPropertyName(#_property);\
	target_class::_getPropertyBag()->AddProperty(kpProp);}

//

#define OvPROPERTY_BAG_END(_classname) ((OvRTTI*)_classname::GetRTTI())->SetPropertyBag(_classname::_getPropertyBag());\
	}\
}	__SPropertiesDeclare_##_classname##_Instance;

//