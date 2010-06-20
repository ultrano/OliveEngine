#pragma once


class OvProperty;
class OvPropertyNode;

class OvPropertyBag
{
public:

	OvPropertyBag():m_pListBegin(0){};
	~OvPropertyBag();

	OvPropertyNode*	BeginProperty();
	OvPropertyNode*	EndProperty();

	OvPropertyNode*		AddProperty(OvProperty* pProperty);

private:

	OvPropertyNode* m_pListBegin;

};

#define OvPROPERTY_BAG_DECL(_classname) private:static OvPropertyBag msh_OvPropertyBag;\
	friend struct __SPropertiesDeclare_##_classname;\
	public:static OvPropertyBag* GetPropertyBag(){return &msh_OvPropertyBag;};\
//

#define	OvPROPERTY_BAG_BEGIN(_classname) OvPropertyBag _classname::msh_OvPropertyBag;\
struct __SPropertiesDeclare_##_classname \
{\
	typedef _classname target_class;\
	__SPropertiesDeclare_##_classname()\
	{\

//

#define OvDECLARE_PROPERTY(_prop_type,_property) {OvProperty* kpProp = new _prop_type;\
	kpProp->SetOffset(offsetof(target_class,_property));\
	kpProp->SetPropertyName(#_property);\
	target_class::GetPropertyBag()->AddProperty(kpProp);}

//

#define OvPROPERTY_BAG_END(_classname) ((OvRTTI*)_classname::GetRTTI())->SetPropertyBag(_classname::GetPropertyBag());\
	}\
}	__SPropertiesDeclare_##_classname##_Instance;

//