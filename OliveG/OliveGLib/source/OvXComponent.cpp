#include "OvXComponent.h"
#include "OvXObject.h"
#include "OvRegisterableProperties.h"
OvRTTI_IMPL(OvXComponent);


OvPROPERTY_BAG_BEGIN(OvXComponent);
	OvPROPERTY_BAG_REGISTER( OvProp_object_pointer, m_equippedObject );
OvPROPERTY_BAG_END(OvXComponent);


OvXComponent::OvXComponent()
:m_equippedObject( NULL )
{
}
OvXComponent::~OvXComponent()
{

}

void		OvXComponent::SetEquippedTarget( OvXObject* _pEquippedObject )
{
	if( ! _pEquippedObject )
		return;

	m_equippedObject = _pEquippedObject;
	_pEquippedObject->EquipExtraComponent( this );
}
OvXObject*	OvXComponent::GetEquippedTarget()
{
	return m_equippedObject;
}

