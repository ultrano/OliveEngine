#pragma once


class OvProperty;
class OvPropertyNode;

class OvPropertyBag
{
public:

	~OvPropertyBag();

	typedef void (*tdRegisterPropertiesCallback)(void);

	OvPropertyBag(tdRegisterPropertiesCallback pCallback);

	OvPropertyNode*	BeginProperty();
	OvPropertyNode*	EndProperty();

	OvPropertyNode*		RegisterProperty(OvProperty* pProperty);

private:

	OvPropertyNode* m_pListBegin;

};

/*
public:static void	RegisterProperties(); �� ���� �ؾ���
*/
#define OvPROP_BAG_DECL(_classname) private:static OvPropertyBag msh_OvPropertyBag;\
	public:static OvPropertyBag* GetPropertyBag(){return &msh_OvPropertyBag;};\
	public:static void	RegisterProperties();

#define OvPROP_BAG_IMPL(_classname) OvPropertyBag _classname::msh_OvPropertyBag(_classname::RegisterProperties);

